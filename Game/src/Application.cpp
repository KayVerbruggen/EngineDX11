#include "Window.h"
#include "Renderer.h"
#include "Timer.h"
#include "Model.h"
#include "Camera.h"
#include "Util.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);
	Renderer renderer(window.GetWindowHandle());
	Camera camera;
	StartTimer();
	Light light;
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	light.dir = XMFLOAT3(0.0f, 0.0f, 1.0f);

	Shader shader("shaders/BasicVS.cso", "shaders/BasicPS.cso");

	std::vector<Vertex> vertices =
	{
		// Front Face
		Vertex{ -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, },
		Vertex{ -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, },
		Vertex{ 1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, },
		Vertex{ 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, },

		// Back Face
		Vertex{ -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, },
		Vertex{ 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, },
		Vertex{ 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, },
		Vertex{ -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, 1.0f, },

		// Top Face
		Vertex{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, },
		Vertex{ -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, },
		Vertex{ 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, },
		Vertex{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, },

		// Bottom Face
		Vertex{ -1.0f, -1.0f, -1.0f,-1.0f, -1.0f, -1.0f, },
		Vertex{ 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, },
		Vertex{ 1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, },
		Vertex{ -1.0f, -1.0f,  1.0f,-1.0f, -1.0f,  1.0f, },

		// Left Face
		Vertex{ -1.0f, -1.0f,  1.0f,  -1.0f, -1.0f,  1.0f, },
		Vertex{ -1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f, },
		Vertex{ -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f, -1.0f, },
		Vertex{ -1.0f, -1.0f, -1.0f,  -1.0f, -1.0f, -1.0f, },

		// Right Face
		Vertex{ 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, },
		Vertex{ 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, },
		Vertex{ 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f, },
		Vertex{ 1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, }
	};

	std::vector<unsigned int> indices =
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	Model test(vertices, indices);

	while (window.IsOpen())
	{
		// Logic and handling user input here
		UpdateTimer();
		camera.Update(GetDeltaTime());

		// Rendering here
		renderer.BeginFrame();

		renderer.Draw(test, camera, light, shader);

		renderer.EndFrame();

		// Reset the timer
		ResetTimer();
	}
}