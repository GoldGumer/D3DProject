#include "Graphics.h"

#include <Windows.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


Graphics::Graphics(HWND* windowHandle)
{
	DXGI_SWAP_CHAIN_DESC sd =
	{
		0, 0, 0, 0,
		DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_UNSPECIFIED,
		0, 0,
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		1,
		*windowHandle, TRUE, DXGI_SWAP_EFFECT_DISCARD,
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
	pSwap->Present(1u, 0);
}

void Graphics::AddToDraw(float x, float y, float z)
{
	Vertex vertexToAdd = Vertex(x, y, z);
	/*if (std::find(vertexList.begin(), vertexList.end(), vertexToAdd) == vertexList.end())
	{
		vertexList.push_back(vertexToAdd);
	}*/
}
