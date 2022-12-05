#include "Window.h"



Window::Window(int spawnX, int spawnY, int length, int height, HINSTANCE hInst, WNDPROC WndProc)
{
	this->length = length;
	this->height = height;

	//Name for the window
	const auto windowName = L"D3DWindow";

	//Setting parameters for the Window
	WNDCLASSEX window = { 0 };
	window.cbSize = sizeof(window);
	window.style = CS_OWNDC;
	window.lpfnWndProc = WndProc;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = hInst;
	window.hIcon = nullptr;
	window.hCursor = nullptr;
	window.hbrBackground = nullptr;
	window.lpszMenuName = nullptr;
	window.lpszClassName = windowName;
	window.hIconSm = nullptr;

	//Registers Window
	RegisterClassEx(&window);

	//Creates Window
	HWND windowHandle = CreateWindowEx(
		0,
		windowName,
		L"D3D Bottle Project",
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

	this->windowHandle = windowHandle;

	ShowWindow(windowHandle, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(windowHandle);
}

void Window::Update(MSG *msg)
{
	TranslateMessage(msg);
	DispatchMessage(msg);
}