#include "Renderer.h"
#include "Util.h"

Renderer::Renderer(HWND windowHandle)
{
	InitDeviceAndSwapchain(windowHandle);
	InitRenderTargetView();
	InitDepthBuffer();
	InitDepthStencilState();
	InitDepthStencilView();

	m_deviceCon->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	InitRasterizerState();
	InitViewport();
}

Renderer::~Renderer()
{
	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;
	}

	if (m_deviceCon)
	{
		m_deviceCon->Release();
		m_deviceCon = nullptr;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}

	if (m_depthBuffer)
	{
		m_depthBuffer->Release();
		m_depthBuffer = nullptr;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = nullptr;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}

	if (m_rasterizerState)
	{
		m_rasterizerState->Release();
		m_rasterizerState = nullptr;
	}
}

void Renderer::InitDeviceAndSwapchain(HWND windowHandle)
{
	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	// Buffer
	sd.BufferCount			= 1;
	sd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Height	= (UINT)SCREEN_HEIGHT;
	sd.BufferDesc.Width		= (UINT)SCREEN_WIDTH;
	sd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD;
	
	// Scanline and scaling are unspecified
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// MSAA
	sd.SampleDesc.Count		= MSAA;
	sd.SampleDesc.Quality	= 0;
	
	// Window settings
	sd.OutputWindow			= windowHandle;
	sd.Windowed				= !FULLSCREEN;

	// No flags
	sd.Flags = 0;

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, 
										D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, nullptr, &m_deviceCon);

	if (hr != S_OK)
		MessageBox(0, "Failed to create Device and Swapchain", "Direct3D 11", MB_OK);
}

void Renderer::InitRenderTargetView()
{
	ID3D11Texture2D* backBuffer;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to get buffer!", "Direct3D 11", MB_OK);

	hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	if (hr != S_OK)
		MessageBox(0, "Failed to create render target view!", "Direct3D 11", MB_OK);

	backBuffer->Release();
}

void Renderer::InitDepthBuffer()
{
	D3D11_TEXTURE2D_DESC depthBufferDesc = { 0 };

	depthBufferDesc.Width = (UINT)SCREEN_WIDTH;
	depthBufferDesc.Height = (UINT)SCREEN_HEIGHT;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.SampleDesc.Count = MSAA;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create depth buffer!", "Direct3D 11", MB_OK);

}

void Renderer::InitDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (hr != S_OK)
		MessageBox(0, "Creating Depth stencil state failed!", "Direct3D 11", MB_OK);

	m_deviceCon->OMSetDepthStencilState(m_depthStencilState, 1);
}

void Renderer::InitDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = m_device->CreateDepthStencilView(m_depthBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (hr != S_OK)
		MessageBox(0, "Failed to create depth stencil view!", "Direct3D 11", MB_OK);
}

void Renderer::InitRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	if (MSAA > 1)
	{
		rasterizerDesc.AntialiasedLineEnable = true;
		rasterizerDesc.MultisampleEnable = true;
	}
	else
	{
		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.MultisampleEnable = false;
	}
	
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	hr = m_device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);
	if (hr != S_OK)
		MessageBox(0, "Creating rasterizer state failed!", "Direct3D 11", MB_OK);

	m_deviceCon->RSSetState(m_rasterizerState);
}

void Renderer::InitViewport()
{
	CD3D11_VIEWPORT vp;

	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinDepth = 0.0;
	vp.MaxDepth = 1.0;

	m_deviceCon->RSSetViewports(1, &vp);
}

void Renderer::BeginFrame()
{
	m_deviceCon->ClearRenderTargetView(m_renderTargetView, DirectX::Colors::Coral);
}

void Renderer::EndFrame()
{
	if (V_SYNC)
	{
		m_swapChain->Present(1, 0);
	} else
	{
		m_swapChain->Present(0, 0);
	}
}