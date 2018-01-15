#include "Window.h"
#include "Renderer.h"
#include "GameTimer.h"
#include "Model.h"
#include "Camera.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);
	Renderer renderer(window.GetWindowHandle());
	GameTimer timer;
	Camera camera(renderer.GetDevice(), renderer.GetDeviceContext());
	Model test(renderer.GetDevice(), renderer.GetDeviceContext());

	while (window.GetMSG().message != WM_QUIT)
	{
		timer.Reset();
		window.HandleMessage();		// Handle the messages first
		timer.Tick();

		camera.Update(timer.DeltaTime());

		// Rendering here
		renderer.BeginFrame();

		test.Draw(camera);

		renderer.EndFrame();
	}
}