#pragma once

#include <d3d11.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>

#include "Model.h"

class Renderer
{
public:
	Renderer(HWND windowHandle);
	~Renderer();

	void BeginFrame();
	void Draw(Model &model, const Camera &cam, const Light &light, Shader &shader);
	void EndFrame();

	void SetClearColor(float r, float g, float b);

	static ID3D11Device* GetDevice() { return m_device; };
	static ID3D11DeviceContext* GetDeviceContext() { return m_deviceCon; };

private:
	// Clear color, so the background.
	float m_clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	// Direct3D interfaces
	static ID3D11Device* m_device;
	static ID3D11DeviceContext* m_deviceCon;
	IDXGISwapChain* m_swapChain;
	
	ID3D11RenderTargetView* m_renderTargetView;

	// Depth stencil stuff
	ID3D11Texture2D* m_depthBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;

	// Rasterizer state
	ID3D11RasterizerState* m_rasterizerState;
	ID3D11RasterizerState* m_rasterizerWireframeState;

	// Blend state
	ID3D11BlendState* m_blendState;

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