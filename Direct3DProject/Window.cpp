#include "Window.h"



Window::Window(int spawnX, int spawnY, int length, int height, HINSTANCE hInst, WNDPROC WndProc)
{
	const auto windowName = L"D3DWindow";
	WNDCLASSEX window = { sizeof(window), CS_OWNDC, WndProc, 0, 0, hInst, nullptr, nullptr, nullptr, nullptr, windowName, nullptr };
	RegisterClassEx(&window);

	HWND windowHandle = CreateWindowEx(
		0,
		windowName,
		L"D3D Bottle Display",
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		spawnX,
		spawnY,
		length,
		height,
		nullptr,
		nullptr,
		hInst,
		nullptr
	);

	ShowWindow(windowHandle, SW_SHOW);
}

void Window::Update(MSG* msg)
{
	DispatchMessage(&msg);
}
