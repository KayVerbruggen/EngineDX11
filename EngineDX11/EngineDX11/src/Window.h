#pragma once

#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, UINT showCmd);
	~Window();

	void HandleMessage();
	MSG& GetMSG();

private:
	HRESULT hr;

	HWND m_windowHandle;
	WNDCLASSEX wc;
	MSG msg;

	// Settings window
	float m_width, m_height;
	const char* m_className = "WindowClass";
	const char* m_windowTitle = "TestGame";
};

