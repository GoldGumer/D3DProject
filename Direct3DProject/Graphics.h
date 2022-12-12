#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <directxmath.h>

#include "Cube.h"
#include "ObjReader.h"

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct ConstantMatrices 
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

class Graphics
{
public:
	Graphics();
	Graphics(HWND windowHandle);
	~Graphics();

	void UpdateScreen();

private:
	void InitBuffers();
	void InitShaders();

	void DrawCube(Cube cube);

	void ClearBuffer(float rgb[3]) noexcept;

	//Cubes to be generated
	Cube cubes[3] =
	{
		Cube(new float[3] { 0.0f, 0.0f, 5.0f }),
		Cube(new float[3] { -5.0f, 0.0f, 5.0f }),
		Cube(new float[3] { 5.0f, 0.0f, 5.0f }),
	};

	//Background RGB
	float bgRGB[3] = { 0.25f,0.25f,0.25f };

	//World projection to screen
	XMMATRIX view;
	XMMATRIX projection;

	//Vertex list
	XMFLOAT3 vertices[8] =
	{
		XMFLOAT3(-1.0f,  1.0f, -1.0f),
		XMFLOAT3(1.0f,  1.0f, -1.0f),
		XMFLOAT3(1.0f,  1.0f,  1.0f),
		XMFLOAT3(-1.0f,  1.0f,  1.0f),
		XMFLOAT3(-1.0f, -1.0f, -1.0f),
		XMFLOAT3(1.0f, -1.0f, -1.0f),
		XMFLOAT3(1.0f, -1.0f,  1.0f),
		XMFLOAT3(-1.0f, -1.0f,  1.0f)
	};

	//Colour list
	XMFLOAT4 colours[2] =
	{
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.5f, 1.0f, 1.0f, 1.0f)
	};

	//Vertex + Colour list
	SimpleVertex verCol[8];

	//Index list
	WORD indices[36] =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};

	HWND windowHandle;

	ID3D11RenderTargetView* pRenderTarget;

	//Buffers
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
	ID3D11Buffer* pConstBuffer;

	//Shaders
	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader* pPixelShader;

	ID3D11InputLayout* pVertexLayout = nullptr;
	D3D11_VIEWPORT viewport;

	//D3D Comms
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

