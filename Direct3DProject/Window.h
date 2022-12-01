#pragma once

#include <Windows.h>

class Window
{
public:
	Window(int spawnX, int spawnY, int length, int height, HINSTANCE hInst, WNDPROC WndProc);
	~Window();
	MSG Update(MSG msg);
private:
	int length, height;
	HWND windowHandle;
};

