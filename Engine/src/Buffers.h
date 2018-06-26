#pragma once

#include <d3d11.h>
#include <vector>

#include "Util.h"

class IndexBuffer 
{
public:
	IndexBuffer(const std::vector<unsigned int>& indices);
	~IndexBuffer();

	// TODO: Maybe we need unbind functions in some weird situation.
	void Bind() const;

private:
	ID3D11Buffer * m_buffer;
};

class VertexBuffer
{
public:
	VertexBuffer(const std::vector<Vertex>& vertices);
	~VertexBuffer();

	// TODO: Maybe we need unbind functions in some weird situation.
	void Bind() const;

private:
	ID3D11Buffer * m_buffer;
};