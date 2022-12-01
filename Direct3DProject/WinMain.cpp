#include <Windows.h>
#include "Window.h"

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
	case WM_QUIT:
		PostQuitMessage(20);
		break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	Window window = Window(200, 200, 640, 480, hInst, WndProc);

	MSG msg;
	bool result;

	while (result = GetMessage(&msg, nullptr, 0, 0) > 0) msg = window.Update(msg);

	OutputDebugString(L"here");

	switch (result)
	{
	case -1:
		return -1;
		break;
	default:
		return msg.wParam;
		break;
	}
}