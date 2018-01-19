#pragma once

#include <vector>
#include <fstream>
#include "Util.h"
#include "Camera.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>
using namespace DirectX;

class Model
{
public:
	Model(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext);
	~Model();

	void Draw(Camera& cam);

private:
	std::vector<Vertex> m_vertices = 
	{
		// Front Face
		Vertex{ -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, -1.0f, -1.0f, },
		Vertex{ -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,  1.0f, -1.0f, },
		Vertex{ 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,  1.0f,  1.0f, -1.0f, },
		Vertex{ 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  1.0f, -1.0f, -1.0f, },

		// Back Face
		Vertex{ -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, },
		Vertex{ 1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 1.0f, },
		Vertex{ 1.0f,  1.0f, 1.0f, 0.0f, 0.0f,  1.0f,  1.0f, 1.0f, },
		Vertex{ -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  1.0f, 1.0f, },

		// Top Face
		Vertex{ -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, -1.0f, },
		Vertex{ -1.0f, 1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 1.0f,  1.0f, },
		Vertex{ 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,  1.0f, },
		Vertex{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,  1.0f, 1.0f, -1.0f, },

		// Bottom Face
		Vertex{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f, },
		Vertex{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, },
		Vertex{ 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, -1.0f,  1.0f, },
		Vertex{ -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,-1.0f, -1.0f,  1.0f, },

		// Left Face
		Vertex{ -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  -1.0f, -1.0f,  1.0f, },
		Vertex{ -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  -1.0f,  1.0f,  1.0f, },
		Vertex{ -1.0f,  1.0f, -1.0f, 1.0f, 0.0f,  -1.0f,  1.0f, -1.0f, },
		Vertex{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, },

		// Right Face
		Vertex{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, },
		Vertex{ 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, -1.0f, },
		Vertex{ 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f, },
		Vertex{ 1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  1.0f, }
	};

	std::vector<unsigned int> m_indices = 
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	void CreateShaders(const char* vsFileName, const char* psFileName);
	void CreateVertexBuffer(const std::vector<Vertex>& vertices);
	void CreateIndexBuffer(const std::vector<unsigned int>& indices);
	void CreateConstantBuffer();
	void InitWorld();
	void LoadTexture(const char* texFile);

	HRESULT hr;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceCon;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

	ID3D11ShaderResourceView* m_texture;
	ID3D11SamplerState* m_textureSamplerState;

	ID3D11Buffer* m_bufferPerObject;
	cbPerObjectStruct cbPerObj;
	ID3D11Buffer* m_bufferPerFrame;
	cbPerFrameStruct cbPerFrame;
	XMMATRIX localWorld;

	DirectionalLight sun;

	float rotY = 0.0f;
	XMMATRIX rotation, scale, translation;
};

