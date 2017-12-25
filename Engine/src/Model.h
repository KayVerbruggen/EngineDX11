#pragma once

#include <vector>
#include <fstream>
#include "Util.h"
#include <d3d11.h>
#include <DirectXMath.h>

class Model
{
public:
	Model(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext);
	~Model();

	void Draw();

private:
	std::vector<Vertex> vertices = 
	{
		{ -0.5f, -0.5f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f,  0.5f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, 0.5f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f }
	};
	std::vector<unsigned int> indices = 
	{
		2, 1, 0,
		3, 2, 0
	};

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceCon;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
};

