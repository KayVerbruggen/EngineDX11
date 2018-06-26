#include "Window.h"
#include "Util.h"

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			DestroyWindow(window);
			break;

		default:
			break;
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(window);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(window, message, wParam, lParam);
	}

	return 0;
}

Window::Window(HINSTANCE hInstance, UINT showCmd)
{
	// Settings window
	DWORD Style = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
	const char* m_className = "WindowClass";
	const char* m_windowTitle = "Game";

	// TODO: Figure out how to change icons.
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIconSm = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = m_className;
	wc.lpszMenuName = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wc);

	m_windowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_className, m_windowTitle, Style,
		0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0, 0, hInstance, 0);

	if (m_windowHandle == NULL)
		MessageBoxA(0, "WindowHandle is still NULL", "Error", MB_OK);

	ShowWindow(m_windowHandle, showCmd);
	ShowCursor(FALSE);
	SetCursorPos((int)SCREEN_WIDTH / 2, (int)SCREEN_HEIGHT / 2);

	UpdateWindow(m_windowHandle);

	SecureZeroMemory(&msg, sizeof(MSG));
}

Window::~Window()
{
}

HWND Window::GetWindowHandle()
{
	return m_windowHandle;
}

bool Window::IsOpen()
{
	if (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
	}
	else
	{
		return false;
	}
}
