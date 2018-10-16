#include "Window.h"
#include "Renderer.h"
#include "Timer.h"
#include "Model.h"
#include "Camera.h"
#include "Util.h"
#include "Mesh.h"

#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	Window window(hInstance, showCmd);
	Renderer renderer(window.GetWindowHandle());
	Camera camera;
	Light light(0.0f, 0.0f, 1.0f);
	Shader shader("shaders/BasicVS.cso", "shaders/BasicPS.cso");

	std::vector<Vertex> vertices =
	{
		// Front Face
		Vertex{ -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
		Vertex{ -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 1.0f },
		Vertex{  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, 1.0f, 1.0f },
		Vertex{  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 1.0f },

		// Back Face
		Vertex{ -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
		Vertex{  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f },
		Vertex{  1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f },
		Vertex{ -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f },

		// Top Face
		Vertex{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
		Vertex{ -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		Vertex{  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f },
		Vertex{  1.0f, 1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 1.0f },

		// Bottom Face
		Vertex{ -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
		Vertex{  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
		Vertex{  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f },
		Vertex{ -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 1.0f },

		// Left Face
		Vertex{ -1.0f, -1.0f,  1.0f,  -1.0f, -1.0f,  1.0f, 0.0f, 0.0f },
		Vertex{ -1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f, 0.0f, 1.0f },
		Vertex{ -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f },
		Vertex{ -1.0f, -1.0f, -1.0f,  -1.0f, -1.0f, -1.0f, 0.0f, 1.0f },

		// Right Face
		Vertex{ 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
		Vertex{ 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 0.0f, 1.0f },
		Vertex{ 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f, 1.0f },
		Vertex{ 1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, 0.0f, 1.0f }
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

	Model cube(Mesh("res/tree.fbx"), Texture(L"res/TextureAtlas.png"));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplWin32_Init(window.GetWindowHandle());
	ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());
	ImGui::StyleColorsDark();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float rot[3] = {0.0f, 0.0f, 0.0f};
	float pos[3] = {0.0f, 0.0f, 0.0f};

	StartTimer();
	while (window.IsOpen())
	{
		// Logic and handling user input here
		UpdateTimer();
		camera.Update(GetDeltaTime());

		// Rendering here
		renderer.BeginFrame();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
			renderer.SetClearColor(clear_color.x, clear_color.y, clear_color.z);

			ImGui::Text("Cube:");
			ImGui::SliderFloat3("Rotation", rot, 0.0f, 360.0f);
			cube.SetRotation(rot[0], rot[1], rot[2]);

			ImGui::SliderFloat3("Position", pos, -10.0f, 10.0f);
			cube.SetPosition(pos[0], pos[1], pos[2]);
		}

		renderer.Draw(cube, camera, light, shader);

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		renderer.EndFrame();

		// Reset the timer
		ResetTimer();
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}