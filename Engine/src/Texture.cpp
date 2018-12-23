#include "Texture.h"

#include "WICTextureLoader.h"
#include "Renderer.h"

Texture::Texture(std::wstring texFile)
{
	D3D11_SAMPLER_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(D3D11_SAMPLER_DESC));
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampleDesc.MinLOD = 0;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	auto hr = Renderer::GetDevice()->CreateSamplerState(&sampleDesc, m_samplerState.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to create sampler state!", "D3D11 Error", MB_OK);

	hr = DirectX::CreateWICTextureFromFile(Renderer::GetDevice().Get(), texFile.c_str(), nullptr, m_texture.GetAddressOf());
	if (hr != S_OK)
		MessageBox(0, "Failed to load texture from file!", "D3D11 Error", MB_OK);
}

Texture::~Texture()
{
	if (m_texture)
	{
		m_texture.Reset();
	}

	if (m_samplerState)
	{
		m_samplerState.Reset();
	}
}

void Texture::Bind() const
{
	Renderer::GetDeviceContext()->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
}