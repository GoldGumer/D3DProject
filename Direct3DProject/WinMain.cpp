#include <Windows.h>

#include "Window.h"

LRESULT CALLBACK WndProc(
	HWND windowHandle,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(20);
		break;
	}

	return DefWindowProc(windowHandle, msg, wParam, lParam );
}

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	INT nCmdShow
)
{
	Window window = Window(200, 200, 640, 480, hInst, WndProc);

	MSG msg;
	bool result;

	Graphics gfx = Graphics(window.getWindowHandle());

	SetTimer(window.getWindowHandle(), 1u, 10, NULL);

	while (result = GetMessage(&msg, nullptr, 0, 0) > 0) 
	{
		gfx.UpdateScreen();
		window.Update(&msg);
	}

	if (result == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}