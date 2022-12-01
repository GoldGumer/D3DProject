#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <list>

#include "Triangle.h"
#include "Vertex.h"

class Graphics
{
public:
	Graphics(HWND* pHWnd);
	~Graphics();
	void UpdateScreen();
	void AddToDraw(float x, float y, float z);
private:
	std::list<Vertex> vertices;

	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

