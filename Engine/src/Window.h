#pragma once

#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, UINT showCmd);
	~Window();

	HWND GetWindowHandle();
	bool IsOpen();

private:
	HWND m_windowHandle;
	MSG msg;
};

