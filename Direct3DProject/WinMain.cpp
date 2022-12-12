#include <Windows.h>

#include "Window.h"

//direction the object is rotating in 
char dir = 'L';

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
	case WM_KEYDOWN:
		if (wParam == 'A')
		{
			dir = 'L';
		}
		else if (wParam == 'W')
		{
			dir = 'U';
		}
		else if (wParam == 'D')
		{
			dir = 'R';
		}
		else if (wParam == 'S')
		{
			dir = 'D';
		}
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
	Window window = Window(250, 50, 1280, 960, hInst, WndProc);

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