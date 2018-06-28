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

	// TODO: Finish these functions.
	//void SetColor(float r, float g, float b, float a);
	void SetPosition(float x, float y, float z);
	void AddPosition(float x, float y, float z);

	void SetRotation(float x, float y, float z);
	void AddRotation(float x, float y, float z);

	inline IndexBuffer& GetIndexBuffer() { return m_indexBuffer; };
	inline VertexBuffer& GetVertexBuffer() { return m_vertexBuffer; };
	inline XMMATRIX GetWorld() const { return m_world; };
	inline unsigned int GetIndexSize() const { return m_indexSize; };

private:
	IndexBuffer m_indexBuffer;
	VertexBuffer m_vertexBuffer;
	unsigned int m_indexSize;

	XMMATRIX m_world;

	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
	XMMATRIX m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_translation;
};

