#include "Window.h"
#include "Util.h"

#include "imgui/imgui_impl_win32.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
		return true;

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
	const char* className = "WindowClass";
	const char* windowTitle = "Game";

	// Window rectangle which will make sure that:
	// the width and height do NOT include the border.
	RECT wr;
	wr.left		= SCREEN_WIDTH/2 - (int)WINDOW_WIDTH/2;
	wr.top		= SCREEN_HEIGHT/2 - (int)WINDOW_HEIGHT/2;
	wr.right	= wr.left + (LONG)WINDOW_WIDTH;
	wr.bottom	= wr.top + (LONG)WINDOW_HEIGHT;
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

	// TODO: Figure out how to change icons.
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIconSm = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = className;
	wc.lpszMenuName = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wc);

	m_windowHandle = CreateWindowEx(WS_EX_APPWINDOW, className, windowTitle, WS_OVERLAPPEDWINDOW,
		wr.left, wr.top, wr.right-wr.left, wr.bottom-wr.top, 0, 0, hInstance, 0);

	if (m_windowHandle == NULL)
		MessageBoxA(0, "WindowHandle is still NULL", "Error", MB_OK);

	//SetWindowLong(m_windowHandle, GWL_STYLE, 0);
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
