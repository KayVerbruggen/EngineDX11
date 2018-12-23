#include "Shader.h"

#include "Renderer.h"

Shader::Shader(std::string vsFileName, std::string psFileName)
{
	// Shader creation
	std::ifstream vsFile(vsFileName, std::ios::binary);
	std::ifstream psFile(psFileName, std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	HRESULT hr = Renderer::GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, m_vertexShader.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to create the vertex shader!", "D3D11 Error", MB_OK);

	hr = Renderer::GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, m_pixelShader.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to create the pixel shader!", "D3D11 Error", MB_OK);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA }
	};

	hr = Renderer::GetDevice()->CreateInputLayout(layout, 3, vsData.data(), vsData.size(), m_inputLayout.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to create input layout", "Direct3D 11 Error", MB_OK);

	// Creating the constant buffers.
	CD3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(CD3D11_BUFFER_DESC));

	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(CBPerObject);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;

	hr = Renderer::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, m_bufferPerObject.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to create constant buffer", "Direct3D 11 Error", MB_OK);

	constantBufferDesc.ByteWidth = sizeof(CBPerFrame);
	hr = Renderer::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, m_bufferPerFrame.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to create constant buffer", "Direct3D 11 Error", MB_OK);
}

Shader::~Shader()
{
	if (m_bufferPerFrame)
	{
		m_bufferPerFrame.Reset();
	}

	if (m_bufferPerObject)
	{	
		m_bufferPerObject.Reset();
	}

	if (m_inputLayout)
	{
		m_inputLayout.Reset();
	}

	if (m_pixelShader)
	{
		m_pixelShader.Reset();
	}

	if (m_vertexShader)
	{
		m_vertexShader.Reset();
	}
}

void Shader::Bind() const
{
	Renderer::GetDeviceContext()->UpdateSubresource(m_bufferPerObject.Get(), 0, nullptr, &m_cbObject, 0, 0);
	Renderer::GetDeviceContext()->VSSetConstantBuffers(0, 1, m_bufferPerObject.GetAddressOf());

	Renderer::GetDeviceContext()->UpdateSubresource(m_bufferPerFrame.Get(), 0, nullptr, &m_cbFrame, 0, 0);
	Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, m_bufferPerFrame.GetAddressOf());

	Renderer::GetDeviceContext()->IASetInputLayout(m_inputLayout.Get());
	Renderer::GetDeviceContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}
