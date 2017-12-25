#include "Window.h"
#include "Renderer.h"
#include "GameTimer.h"
#include "Model.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);
	Renderer renderer(window.GetWindowHandle());
	GameTimer timer;
	Model test(renderer.GetDevice(), renderer.GetDeviceContext());

	while (window.GetMSG().message != WM_QUIT)
	{
		timer.Reset();
		window.HandleMessage();		// Handle the messages first
		timer.Tick();

		// Rendering here
		renderer.BeginFrame();

		test.Draw();

		renderer.EndFrame();
	}
}