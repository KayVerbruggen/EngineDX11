#include "Model.h"

#include "Renderer.h"

Model::Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices) 
	: m_indexBuffer(indices), m_vertexBuffer(vertices)
{
	m_indexSize = (unsigned int)indices.size();

	m_world = XMMatrixIdentity();

	XMVECTOR rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	rotation = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(0.0f));
	translation = XMMatrixTranslation(0.0f, 0.0f, 4.0f);

	//Set the model's world space using the transformations
	m_world = translation * rotation;
}

Model::~Model()
{
}