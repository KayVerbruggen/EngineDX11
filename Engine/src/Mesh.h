#pragma once

#include <string>

#include "Buffers.h"

class Mesh
{
public:
	Mesh(std::string meshFile);
	~Mesh();

	unsigned int GetMeshCount() { return meshCount; };
	inline unsigned int GetIndexSize(unsigned int index) const { return m_indexSize[index]; };
	inline IndexBuffer& GetIndexBuffer(unsigned int index) { return m_indexBuffers[index]; };
	inline VertexBuffer& GetVertexBuffer(unsigned int index) { return m_vertexBuffers[index]; };
private:

	std::vector<IndexBuffer> m_indexBuffers;
	std::vector<VertexBuffer> m_vertexBuffers;
	std::vector<unsigned int> m_indexSize;
	unsigned int meshCount;
};

