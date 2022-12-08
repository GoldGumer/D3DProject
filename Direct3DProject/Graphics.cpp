#include "Graphics.h"

#include <Windows.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

Graphics::Graphics()
{
}

Graphics::Graphics(HWND windowHandle)
{
	this->windowHandle = windowHandle;

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
	sd.BufferDesc.RefreshRate.Numerator = 0;
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

	//Vertex Buffer setup
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//bufferDesc.CPUAccessFlags = 0u;
	//bufferDesc.MiscFlags = 0u;
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * ARRAYSIZE(vertices);
	//bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subResData = { vertices, 0, 0 };
	pDevice->CreateBuffer(&bufferDesc, &subResData, &pVertexBuffer);


	ID3DBlob* pBlob;

	//Pixel shader
	D3DReadFileToBlob(L"pixelshader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	pContext->PSSetShader(pPixelShader, nullptr, 0u);

	//Vertex shader
	D3DReadFileToBlob(L"vertexshader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	pContext->VSSetShader(pVertexShader, nullptr, 0u);

	//render target setup
	ID3D11Texture2D* pBackBuffer;
	pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTarget);
	pBackBuffer->Release();
	pContext->OMSetRenderTargets(1, &pRenderTarget, nullptr);

	//creating input layer
	ID3D11InputLayout* pInputLay;
	const D3D11_INPUT_ELEMENT_DESC ied[] = { { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 } };
	pDevice->CreateInputLayout(ied, ARRAYSIZE(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLay);
	pContext->IASetInputLayout(pInputLay);
	//pContext->IAGetInputLayout(&pInputLay);
	
	//setup viewport
	RECT winRect;
	GetClientRect(windowHandle, &winRect);

	D3D11_VIEWPORT vp = {0};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (FLOAT)(winRect.right - winRect.left);
	vp.Height = (FLOAT)(winRect.bottom - winRect.top);

	pContext->RSSetViewports(1u, &vp);
}

Graphics::~Graphics()
{
	if (pSwap != nullptr)
	{
		pSwap->Release();
	}
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}
	if (pContext != nullptr)
	{
		pContext->Release();
	}
}

void Graphics::UpdateScreen()
{
	ClearBuffer(rColor, gColor, bColor);
	pContext->OMSetRenderTargets(1, &pRenderTarget, nullptr);
	/*rColor += 0.01f;
	gColor += 0.01f;
	bColor += 0.01f;
	if (rColor >= 1.0f) rColor -= 1.0f;
	if (gColor >= 1.0f) gColor -= 1.0f;
	if (bColor >= 1.0f) bColor -= 1.0f;*/

	//Set Vertex Buffer
	const UINT stride = sizeof(SimpleVertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

	//Primitive Triangle
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pContext->Draw(3u, 0u);
	pSwap->Present(1u, 0u);
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pRenderTarget, color);
}
