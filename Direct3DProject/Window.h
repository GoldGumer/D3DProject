#pragma once
#include <Windows.h>

class Window
{
public:
	Window(int spawnX, int spawnY, int length, int height, HINSTANCE hInst, WNDPROC WndProc);
	void Update(MSG* pMsg);
private:
	int spawnX, spawnY, length, height;
};

