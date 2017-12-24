#include "Window.h"
#include "Renderer.h"
#include "GameTimer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);
	Renderer renderer(window.GetWindowHandle());
	GameTimer timer;

	while (window.GetMSG().message != WM_QUIT)
	{
		timer.Reset();
		window.HandleMessage();		// Handle the messages first
		timer.Tick();

		// Rendering here
		renderer.BeginFrame();

		renderer.EndFrame();
	}
}