#pragma once

#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, UINT showCmd);
	~Window();

	void HandleMessage();
	MSG& GetMSG();
	HWND GetWindowHandle();

private:
	HRESULT hr;

	HWND m_windowHandle;
	WNDCLASSEX wc;
	MSG msg;

	// Settings window
	const char* m_className = "WindowClass";
	const char* m_windowTitle = "Game";
};

