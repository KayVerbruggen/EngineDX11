#include "Model.h"

#include "Renderer.h"

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture)
{
	m_world = XMMatrixIdentity();
	m_mesh = mesh;
	m_texture = texture;

	XMVECTOR rotAxis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_rotationX = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(0.0f));

	rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_rotationY = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(0.0f));

	rotAxis = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	m_rotationZ = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(0.0f));

	m_translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	m_scale = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);

	//Set the model's world space using the transformations
	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}

Model::~Model()
{
}

void Model::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
	
	m_translation = XMMatrixTranslation(x, y, z);
	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}

void Model::AddPosition(float x, float y, float z)
{
	m_posX += x;
	m_posY += y;
	m_posZ += z;

	m_translation = XMMatrixTranslation(m_posX, m_posY, m_posZ);
	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}

void Model::SetRotation(float x, float y, float z)
{
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;

	XMVECTOR rotAxis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_rotationX = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(x));

	rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_rotationY = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(y));

	rotAxis = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	m_rotationZ = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(z));

	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}

void Model::AddRotation(float x, float y, float z)
{
	m_rotX += x;
	m_rotY += y;
	m_rotZ += z;

	XMVECTOR rotAxis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_rotationX = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(m_rotX));
																   
	rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);				   
	m_rotationY = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(m_rotY));
																  
	rotAxis = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);				  
	m_rotationZ = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(m_rotZ));

	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}

void Model::SetScale(float x, float y, float z)
{
	m_scaleX = x;
	m_scaleY = y;
	m_scaleZ = z;

	m_scale = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);
	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}

void Model::AddScale(float x, float y, float z)
{
	m_scaleX += x;
	m_scaleY += y;
	m_scaleZ += z;

	m_scale = XMMatrixScaling(m_scaleX, m_scaleY, m_scaleZ);
	m_world = m_scale * (m_rotationX * m_rotationY * m_rotationZ) * m_translation;
}