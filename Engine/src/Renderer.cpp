#include "Renderer.h"
#include "Util.h"

ID3D11Device* Renderer::m_device;
ID3D11DeviceContext* Renderer::m_deviceCon;

Renderer::Renderer(HWND windowHandle)
{
	InitDeviceAndSwapchain(windowHandle);
	InitRenderTargetView();
	InitDepthBuffer();
	InitDepthStencilState();
	InitDepthStencilView();
	InitRasterizerState();
	InitViewport();
	InitAlphaBlendState();

	m_modelShader = std::make_unique<Shader>("shaders/ModelVS.cso", "shaders/ModelPS.cso");
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
	sd.BufferDesc.Height    = WINDOW_HEIGHT;
	sd.BufferDesc.Width     = WINDOW_WIDTH;
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

	UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0,
										D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, nullptr, &m_deviceCon);

	if (hr != S_OK)
		MessageBox(0, "Failed to create Device and Swapchain", "Direct3D 11 Error", MB_OK);

	m_deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::InitRenderTargetView()
{
	ID3D11Texture2D* backBuffer;
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to get buffer!", "Direct3D 11 Error", MB_OK);

	hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	if (hr != S_OK)
		MessageBox(0, "Failed to create render target view!", "Direct3D 11 Error", MB_OK);

	backBuffer->Release();
}

void Renderer::InitDepthBuffer()
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));

	depthBufferDesc.Width = (UINT)WINDOW_WIDTH;
	depthBufferDesc.Height = (UINT)WINDOW_HEIGHT;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.SampleDesc.Count = MSAA;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	HRESULT hr = m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthBuffer);
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
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	HRESULT hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (hr != S_OK)
		MessageBox(0, "Creating Depth stencil state failed!", "Direct3D 11 Error", MB_OK);

	m_deviceCon->OMSetDepthStencilState(m_depthStencilState, 1);
}

void Renderer::InitDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	HRESULT hr = m_device->CreateDepthStencilView(m_depthBuffer, &depthStencilViewDesc, &m_depthStencilView);
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

	HRESULT hr = m_device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);
	if (hr != S_OK)
		MessageBox(0, "Creating rasterizer state failed!", "Direct3D 11 Error", MB_OK);

	m_deviceCon->RSSetState(m_rasterizerState);

	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;

	hr = m_device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerWireframeState);
	if (hr != S_OK)
		MessageBox(0, "Creating rasterizer state failed!", "Direct3D 11 Error", MB_OK);
}

void Renderer::InitViewport()
{
	D3D11_VIEWPORT vp;

	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)WINDOW_WIDTH;
	vp.Height = (float)WINDOW_HEIGHT;
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

	HRESULT hr = m_device->CreateBlendState(&blendStateDesc, &m_blendState);
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
	m_deviceCon->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	m_deviceCon->ClearRenderTargetView(m_renderTargetView, m_clearColor);
	m_deviceCon->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 1);

	if (GetAsyncKeyState(VK_TAB))
	{
		m_deviceCon->RSSetState(m_rasterizerWireframeState);
	}
	else
	{
		m_deviceCon->RSSetState(m_rasterizerState);
	}
}

void Renderer::Draw(Model &model, const Camera &cam, const Light &light)
{
	m_modelShader->SetView(cam.GetView());
	m_modelShader->SetWorld(model.GetWorld());
	m_modelShader->SetProjection(cam.GetProjection());
	m_modelShader->SetLight(light);
	m_modelShader->Bind();
	
	model.GetTexture().Bind();

	for (unsigned int i = 0; i < model.GetMesh().GetMeshCount(); i++)
	{
		model.GetMesh().GetVertexBuffer(i).Bind();
		model.GetMesh().GetIndexBuffer(i).Bind();

		m_deviceCon->DrawIndexed((UINT)model.GetMesh().GetIndexSize(i), 0, 0);
	}
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

void Renderer::SetClearColor(float r, float g, float b)
{
	m_clearColor[0] = r;
	m_clearColor[1] = g;
	m_clearColor[2] = b;
}
