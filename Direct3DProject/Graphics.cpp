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
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = windowHandle;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

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

	AddToDraw(-1, 0, 0);
	AddToDraw(1, 0, 0);
	AddToDraw(0, 2, 0);

	//Shader Buffers
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA subResData = {};
	subResData.pSysMem = vertices;

	pDevice->CreateBuffer(&bufferDesc, &subResData, &pVertexBuffer);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);
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

	//creating input layer
	ID3D11InputLayout* pInputLay;
	const D3D11_INPUT_ELEMENT_DESC ied[] = { { "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 } };
	pDevice->CreateInputLayout(ied, sizeof(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLay);
	pContext->IAGetInputLayout(&pInputLay);

	//Primitive Triangle
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//setup viewport
	D3D11_VIEWPORT vp;
	vp.Width = 600;
	vp.Height = 800;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

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
	pContext->OMSetRenderTargets(1, &pRenderTarget, nullptr);
	ClearBuffer(rColor, gColor, bColor);
	gColor += 0.01f;
	bColor += 0.04f;
	if (gColor >= 1.0f) gColor -= 1.0f;
	if (bColor >= 1.0f) bColor -= 1.0f;
	pContext->Draw((UINT)sizeof(vertices), 0u);
	pSwap->Present(1u, 0u);
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pRenderTarget, color);
}

void Graphics::AddToDraw(float x, float y, float z)
{
	for (int i = 0; i < 3; i++) if (vertices[i].GetPos() == Vertex().GetPos()) vertices[i] = Vertex(x, y, z);
}
