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
	default:
		break;
	}
}

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	Window window = Window(200, 200, 640, 480, hInst, WndProc);
}