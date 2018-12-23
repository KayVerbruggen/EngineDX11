#pragma once

#include <string>
#include <d3d11.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;

class Texture
{
public:
	Texture(std::wstring texFile);
	~Texture();

	void Bind() const;
private:
	ComPtr<ID3D11ShaderResourceView> m_texture;
	ComPtr<ID3D11SamplerState> m_samplerState;
};

