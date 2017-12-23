#include <Window.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);

	while (window.GetMSG().message != WM_QUIT)
	{
		window.HandleMessage();
	}
}