#pragma once

#include <vector>
#include <fstream>
#include "Util.h"
#include "Camera.h"
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class Model
{
public:
	Model(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext);
	~Model();

	void Draw(Camera& cam);

private:
	std::vector<Vertex> vertices = 
	{
		{ -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f },
		{ -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f },
		{  1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f },
		{  1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f },
		{ -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f },
		{ -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f },
		{  1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f },
		{  1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f },
	};
	std::vector<unsigned int> indices = 
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceCon;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

	ID3D11Buffer* m_bufferPerObject;
	cbPerObject cbPerObj;
	XMMATRIX localWorld;

	float rotY = 0.0f;
	XMMATRIX rotation, scale, translation;
};

