#include "Terrain.h"

std::vector<Vertex> vertices = {
	Vertex {-0.5, 0.0, -0.5, 0.0, 1.0f, 0.0,  0.0,  0.0},
	Vertex { 0.5, 0.0, -0.5, 0.0, 1.0f, 0.0, 100.0,  0.0},
	Vertex { 0.5, 0.0,  0.5, 0.0, 1.0f, 0.0, 100.0, 100.0},
	Vertex {-0.5, 0.0,  0.5, 0.0, 1.0f, 0.0,  0.0, 100.0}
};

std::vector<unsigned int> indices = {
	2, 1, 0,
	3, 2, 0
};

Terrain::Terrain(std::shared_ptr<Texture> tex, float width, float depth)
	: m_vb(vertices), m_ib(indices)
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_width = width;
	m_depth = depth;

	m_tex = tex;

	m_world = XMMatrixScaling(m_width, 1.0, m_depth) * XMMatrixTranslation(m_posX, m_posY, m_posZ);
}

Terrain::~Terrain()
{
}
