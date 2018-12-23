#pragma once

#include "Buffers.h"
#include "Texture.h"

class Terrain
{
public:
	Terrain(std::shared_ptr<Texture> tex, float width, float depth);
	~Terrain();

	inline IndexBuffer& GetIndexBuffer() { return m_ib; };
	inline VertexBuffer& GetVertexBuffer() { return m_vb; };
	inline XMMATRIX& GetWorld() { return m_world; };
	inline std::shared_ptr<Texture> GetTexture() { return m_tex; };

private:
	IndexBuffer m_ib;
	VertexBuffer m_vb;

	std::shared_ptr<Texture> m_tex;

	float m_posX, m_posY, m_posZ;
	float m_width, m_depth;
	XMMATRIX m_world;
};