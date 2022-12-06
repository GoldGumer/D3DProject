#pragma once

#include <Windows.h>

#include "Graphics.h"

class Window
{
public:
	Window(int spawnX, int spawnY, int length, int height, HINSTANCE hInst, WNDPROC WndProc);
	~Window();
	void Update(MSG *msg);
	HWND getWindowHandle();
private:
	int length, height;
	HWND windowHandle;
};