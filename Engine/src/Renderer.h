#pragma once

#include <d3d11.h>
#include <DirectXColors.h>
//#include <d3dcompiler.h>
#include <wrl/client.h>

#include "Model.h"
#include "Shader.h"

using namespace Microsoft::WRL;

class Renderer
{
public:
	Renderer(HWND windowHandle);
	~Renderer();

	void BeginFrame();
	void Draw(std::shared_ptr<Model> model, const Camera &cam, const Light &light);
	void EndFrame();

	void SetClearColor(float r, float g, float b);

	static ComPtr<ID3D11Device> GetDevice() { return m_device; };
	static ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_deviceCon; };

private:
	// Clear color, so the background.
	float m_clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	// Shaders, so the client doesn't have to deal with them.
	std::unique_ptr<Shader> m_modelShader;

	// Direct3D interfaces
	static ComPtr<ID3D11Device> m_device;
	static ComPtr<ID3D11DeviceContext> m_deviceCon;
	ComPtr<ID3D11Debug> m_debugInterface;
	ComPtr<IDXGISwapChain> m_swapChain;
	
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// Depth stencil stuff
	ComPtr<ID3D11Texture2D> m_depthBuffer;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	// Rasterizer state
	ComPtr<ID3D11RasterizerState> m_rasterizerState;
	ComPtr<ID3D11RasterizerState> m_rasterizerWireframeState;

	// Blend state
	ComPtr<ID3D11BlendState> m_blendState;

	// Functions for initializing.
	void InitDeviceAndSwapchain(HWND windowHandle);
	void InitRenderTargetView();
	void InitDepthBuffer();
	void InitDepthStencilState();
	void InitDepthStencilView();
	void InitRasterizerState();
	void InitViewport();
	void InitAlphaBlendState();
};