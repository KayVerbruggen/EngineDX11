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
	InitAlphaBlendState();
}

Renderer::~Renderer()
{
	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	if (m_deviceCon)
	{
		m_deviceCon->Release();
		m_deviceCon = 0;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}

	if (m_depthBuffer)
	{
		m_depthBuffer->Release();
		m_depthBuffer = 0;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if (m_rasterizerState)
	{
		m_rasterizerState->Release();
		m_rasterizerState = 0;
	}
}

void Renderer::InitDeviceAndSwapchain(HWND windowHandle)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

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

	// Refresh rate
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = (UINT)REFRESH_RATE;

	// No flags
	sd.Flags = 0;

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, 
										D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, nullptr, &m_deviceCon);

	if (hr != S_OK)
		MessageBox(0, "Failed to create Device and Swapchain", "Direct3D 11 Error", MB_OK);
}

void Renderer::InitRenderTargetView()
{
	ID3D11Texture2D* backBuffer;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to get buffer!", "Direct3D 11 Error", MB_OK);

	hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	if (hr != S_OK)
		MessageBox(0, "Failed to create render target view!", "Direct3D 11 Error", MB_OK);

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
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create depth buffer!", "Direct3D 11 Error", MB_OK);

}

void Renderer::InitDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

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
		MessageBox(0, "Creating Depth stencil state failed!", "Direct3D 11 Error", MB_OK);

	m_deviceCon->OMSetDepthStencilState(m_depthStencilState, 1);
}

void Renderer::InitDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	depthStencilViewDesc.Flags = 0;

	hr = m_device->CreateDepthStencilView(m_depthBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (hr != S_OK)
		MessageBox(0, "Failed to create depth stencil view!", "Direct3D 11 Error", MB_OK);
}

void Renderer::InitRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	
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
		MessageBox(0, "Creating rasterizer state failed!", "Direct3D 11 Error", MB_OK);

	m_deviceCon->RSSetState(m_rasterizerState);

	D3D11_RASTERIZER_DESC rasterizerWireframeDesc;
	ZeroMemory(&rasterizerWireframeDesc, sizeof(D3D11_RASTERIZER_DESC));

	if (MSAA > 1)
	{
		rasterizerWireframeDesc.AntialiasedLineEnable = true;
		rasterizerWireframeDesc.MultisampleEnable = true;
	}
	else
	{
		rasterizerWireframeDesc.AntialiasedLineEnable = false;
		rasterizerWireframeDesc.MultisampleEnable = false;
	}

	rasterizerWireframeDesc.CullMode = D3D11_CULL_BACK;
	rasterizerWireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerWireframeDesc.DepthBias = 0;
	rasterizerWireframeDesc.DepthBiasClamp = 0.0;
	rasterizerWireframeDesc.DepthClipEnable = true;
	rasterizerWireframeDesc.FrontCounterClockwise = false;
	rasterizerWireframeDesc.ScissorEnable = false;
	rasterizerWireframeDesc.SlopeScaledDepthBias = 0.0f;

	hr = m_device->CreateRasterizerState(&rasterizerWireframeDesc, &m_rasterizerWireframeState);
	if (hr != S_OK)
		MessageBox(0, "Creating rasterizer state failed!", "Direct3D 11 Error", MB_OK);
}

void Renderer::InitViewport()
{
	CD3D11_VIEWPORT vp;

	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_deviceCon->RSSetViewports(1, &vp);
}

void Renderer::InitAlphaBlendState()
{
	D3D11_BLEND_DESC blendStateDesc;
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));

	blendStateDesc.RenderTarget[0].BlendEnable = true;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	blendStateDesc.AlphaToCoverageEnable = false;

	hr = m_device->CreateBlendState(&blendStateDesc, &m_blendState);
	if (hr != S_OK)
		MessageBox(0, "Failed to create blend state", "Direct3D 11 Error", MB_OK);

	float blendFactor[4];
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	m_deviceCon->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
}

void Renderer::BeginFrame()
{
	m_deviceCon->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
	m_deviceCon->ClearRenderTargetView(m_renderTargetView, DirectX::Colors::Black);

	if (GetAsyncKeyState(VK_TAB))
	{
		m_deviceCon->RSSetState(m_rasterizerWireframeState);
	}
	else
	{
		m_deviceCon->RSSetState(m_rasterizerState);
	}

	m_deviceCon->OMSetDepthStencilState(m_depthStencilState, 1);
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

ID3D11Device*& Renderer::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext*& Renderer::GetDeviceContext()
{
	return m_deviceCon;
}