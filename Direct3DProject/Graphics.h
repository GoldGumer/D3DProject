#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <directxmath.h>

#include "Triangle.h"
//#include "Vertex.h"

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Pos;
};

class Graphics
{
public:
	Graphics();
	Graphics(HWND windowHandle);
	~Graphics();
	void UpdateScreen();
	void ClearBuffer(float red, float blue, float green) noexcept;
	//void AddToDraw(float x, float y, float z);
private:
	float rColor = 0.1f;
	float gColor = 0.1f;
	float bColor = 0.1f;

	//Vertex vertices[3] = { Vertex(-1000,0,0) ,Vertex(1000,0,10000) ,Vertex(0,1000,0) };

	SimpleVertex vertices[3] = {
		XMFLOAT3(0.0f, 0.5f, 0.5f),
		XMFLOAT3(0.5f, -0.5f, 0.5f),
		XMFLOAT3(-0.5f, -0.5f, 0.5f),
	};

	HWND windowHandle;

	ID3D11RenderTargetView* pRenderTarget;

	ID3D11Buffer* pVertexBuffer;
	ID3D11VertexShader* pVertexShader;

	ID3D11Buffer* pPixelBuffer;
	ID3D11PixelShader* pPixelShader;

	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

