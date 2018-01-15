#include "Window.h"
#include "Renderer.h"
#include "Timer.h"
#include "Model.h"
#include "Camera.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);
	Renderer renderer(window.GetWindowHandle());
	Camera camera(renderer.GetDevice(), renderer.GetDeviceContext());
	Model test(renderer.GetDevice(), renderer.GetDeviceContext());
	StartTimer();

	while (window.GetMSG().message != WM_QUIT)
	{
		// Handle the messages first
		window.HandleMessage();
		
		// Logic and handling user input here
		UpdateTimer();
		camera.Update(GetDeltaTime());

		// Rendering here
		renderer.BeginFrame();

		test.Draw(camera);

		renderer.EndFrame();

		// Reset the timer
		ResetTimer();
	}
}