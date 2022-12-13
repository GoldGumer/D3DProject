#include "Graphics.h"

#include <Windows.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

void Graphics::InitBuffers()
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0;

	//Vertex Buffer setup
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * ARRAYSIZE(vertices);

	D3D11_SUBRESOURCE_DATA subResData = { vertices, 0, 0 };
	pDevice->CreateBuffer(&bufferDesc, &subResData, &pVertexBuffer);

	const UINT stride = sizeof(SimpleVertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

	//Index Buffer setup
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(WORD) * ARRAYSIZE(indices);

	subResData.pSysMem = indices;
	pDevice->CreateBuffer(&bufferDesc, &subResData, &pIndexBuffer);

	pContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//Constant Buffer stetup
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = sizeof(ConstantMatrices);

	pDevice->CreateBuffer(&bufferDesc, NULL, &pConstBuffer);
}

void Graphics::InitShaders()
{
	ID3DBlob* pBlob;
	//Pixel shader
	D3DReadFileToBlob(L"pixelshader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//Vertex shader
	D3DReadFileToBlob(L"vertexshader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	//creating input layer
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	pDevice->CreateInputLayout(ied, ARRAYSIZE(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pVertexLayout);

	pContext->IASetInputLayout(pVertexLayout);

	pBlob->Release();
}

Graphics::Graphics()
{
}

Graphics::Graphics(HWND windowHandle)
{
	this->windowHandle = windowHandle;

	RECT winRect;
	GetClientRect(windowHandle, &winRect);

	width = winRect.right - winRect.left;
	height = winRect.bottom - winRect.top;

	for (int i = 0; i < ARRAYSIZE(vertices); i++)
	{
		vertices[i].AddColor(colours[i % ARRAYSIZE(colours)]);
	}

	for (int i = 0; i < ARRAYSIZE(indices); i++)
	{
		indices[i] -= 1;
	}

	DXGI_SWAP_CHAIN_DESC sd =
	{
		0, 0, 0, 0,
		DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_UNSPECIFIED,
		0, 0,
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		1,
		windowHandle, TRUE, DXGI_SWAP_EFFECT_DISCARD,
		0
	};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);

	InitBuffers();

	InitShaders();

	//render target setup
	ID3D11Texture2D* pBackBuffer;
	pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTarget);

	D3D11_DEPTH_STENCIL_DESC dsDesc =
	{
		TRUE,
		D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_COMPARISON_LESS
	};

	ID3D11DepthStencilState* dsState;
	pDevice->CreateDepthStencilState(&dsDesc, &dsState);

	pContext->OMSetDepthStencilState(dsState, 1u);
	D3D11_TEXTURE2D_DESC depthTextureDesc =
	{
		(UINT)width,
		(UINT)height,
		1u,
		1u,
		DXGI_FORMAT_D32_FLOAT,
		{ 1u, 0u },
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL
	};

	pDevice->CreateTexture2D(&depthTextureDesc, nullptr, &pDepthTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc =
	{
		DXGI_FORMAT_D32_FLOAT,
		D3D11_DSV_DIMENSION_TEXTURE2D,
		0u
	};

	pDevice->CreateDepthStencilView(pDepthTexture, &dsvDesc, &pDepthStencil);

	pBackBuffer->Release();

	pContext->OMSetRenderTargets(1, &pRenderTarget, pDepthStencil);
	
	//setup viewport
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	pContext->RSSetViewports(1u, &viewport);

	//Constant Matrices setup
	view = XMMatrixLookAtLH(XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / height, 0.01f, 100.0f);
}

Graphics::~Graphics()
{
	//Buffers
	if (pVertexBuffer) pVertexBuffer->Release();
	if (pIndexBuffer) pIndexBuffer->Release();
	if (pConstBuffer) pConstBuffer->Release();
	if (pDepthStencil) pDepthStencil->Release();

	if (pDepthTexture) pDepthTexture->Release();

	//Shaders
	if (pPixelShader) pPixelShader->Release();
	if (pVertexShader) pVertexShader->Release();
	if (pVertexLayout) pVertexLayout->Release();

	//D3D Comms
	if (pDevice) pDevice->Release();
	if (pSwap) pSwap->Release();
	if (pContext) pContext->Release();
}

void Graphics::UpdateScreen()
{
	ClearBuffer(bgRGB);
	pContext->OMSetRenderTargets(1, &pRenderTarget, pDepthStencil);

	//Primitive Triangle
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Setup for drawing to backbuffer
	pContext->VSSetShader(pVertexShader, nullptr, 0u);
	pContext->VSSetConstantBuffers(0, 1, &pConstBuffer);
	pContext->PSSetShader(pPixelShader, nullptr, 0u);

	//Goes through each cube and draws them
	for (int i = 0; i < ARRAYSIZE(objects); i++)
	{
		DrawObject(objects[i]);
	}

	//Swap back buffer
	pSwap->Present(1u, 0u);
}

void Graphics::DrawObject(Object cube)
{
	ConstantMatrices cm;

	//Transforming
	cm.world = XMMatrixTranspose(cube.GetWorld());
	cm.view = XMMatrixTranspose(view);
	cm.projection = XMMatrixTranspose(projection);

	//Update to new Transform
	pContext->UpdateSubresource(pConstBuffer, 0, nullptr, &cm, 0, 0);

	//Drawing
	pContext->DrawIndexed(ARRAYSIZE(indices), 0u, 0);
}

void Graphics::ClearBuffer(float rgb[3]) noexcept
{
	const float color[] = { rgb[0], rgb[1], rgb[2], 1.0f };
	pContext->ClearRenderTargetView(pRenderTarget, color);
	pContext->ClearDepthStencilView(pDepthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0u);
}
