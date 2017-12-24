#pragma once

#include <d3d11.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>

class Renderer
{
public:
	Renderer(HWND windowHandle);
	~Renderer();

	void BeginFrame();
	void EndFrame();

	ID3D11Device*& GetDevice();
	ID3D11DeviceContext*& GetDeviceContext();
private:
	// Used for error checking
	HRESULT hr;

	// Direct3D interfaces
	// TODO: Check if devices can get lost like with D3D9.
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceCon;
	IDXGISwapChain* m_swapChain;
	
	ID3D11RenderTargetView* m_renderTargetView;

	// Depth stencil stuff
	ID3D11Texture2D* m_depthBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;

	// Rasterizer state
	ID3D11RasterizerState* m_rasterizerState;

	// Functions for initializing.
	void InitDeviceAndSwapchain(HWND windowHandle);
	void InitRenderTargetView();
	void InitDepthBuffer();
	void InitDepthStencilState();
	void InitDepthStencilView();
	void InitRasterizerState();
	void InitViewport();
};