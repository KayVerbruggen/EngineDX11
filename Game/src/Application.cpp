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

	auto tree = std::make_shared<Model>(std::make_shared<Mesh>("res/tree.fbx"), std::make_shared<Texture>(L"res/TextureAtlas.png"));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplWin32_Init(window.GetWindowHandle());
	ImGui_ImplDX11_Init(Renderer::GetDevice().Get(), Renderer::GetDeviceContext().Get());
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
			tree->SetRotation(rot[0], rot[1], rot[2]);

			ImGui::SliderFloat3("Position", pos, -10.0f, 10.0f);
			tree->SetPosition(pos[0], pos[1], pos[2]);
		}

		renderer.Draw(tree, camera, light);

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