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
#include "Texture.h"

class Model
{
public:
	Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture texture);
	~Model();

	void SetPosition(float x, float y, float z);
	void AddPosition(float x, float y, float z);
	
	void SetRotation(float x, float y, float z);
	void AddRotation(float x, float y, float z);

	Texture GetTexture() { return m_texture; };
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

	Texture m_texture;
};

