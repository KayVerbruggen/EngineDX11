#pragma once

#include <string>
#include <d3d11.h>

class Texture
{
public:
	Texture(std::wstring texFile);
	~Texture();

	void Bind() const;
private:
	ID3D11ShaderResourceView* m_texture;
	ID3D11SamplerState* m_samplerState;
};

