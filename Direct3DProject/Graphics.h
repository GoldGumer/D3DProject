#pragma once

#include <Windows.h>
#include <d3d11.h>

#include "Triangle.h"
#include "Vertex.h"

class Graphics
{
public:
	Graphics();
	Graphics(HWND windowHandle);
	~Graphics();
	void UpdateScreen();
	void ClearBuffer(float red, float blue, float green) noexcept;
	void AddToDraw(float x, float y, float z);
private:
	float rColor = 0.0f;
	float gColor = 0.0f;
	float bColor = 0.0f;

	Vertex vertices[3];

	ID3D11RenderTargetView* pRenderTarget;

	ID3D11Buffer* pVertexBuffer;
	ID3D11VertexShader* pVertexShader;

	ID3D11Buffer* pPixelBuffer;
	ID3D11PixelShader* pPixelShader;

	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

