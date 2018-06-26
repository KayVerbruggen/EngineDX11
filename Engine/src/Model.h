#pragma once

#include <vector>
#include <fstream>
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#include "Util.h"
#include "Camera.h"
#include "Buffers.h"
#include "Shader.h"

class Model
{
public:
	Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Model();

	inline IndexBuffer& GetIndexBuffer() { return m_indexBuffer; };
	inline VertexBuffer& GetVertexBuffer() { return m_vertexBuffer; };
	inline XMMATRIX GetWorld() const { return m_world; };
	inline unsigned int GetIndexSize() const { return m_indexSize; };

private:
	IndexBuffer m_indexBuffer;
	VertexBuffer m_vertexBuffer;
	unsigned int m_indexSize;

	XMMATRIX m_world;
	Light sun;

	float rotX, rotY, rotZ;
	XMMATRIX rotation, scale, translation;
};

