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
#include "Mesh.h"

class Model
{
public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);
	~Model();

	void SetPosition(float x, float y, float z);
	void AddPosition(float x, float y, float z);
	
	void SetRotation(float x, float y, float z);
	void AddRotation(float x, float y, float z);
	
	void SetScale(float x, float y, float z);
	void AddScale(float x, float y, float z);

	std::shared_ptr<Texture> GetTexture() { return m_texture; };
	std::shared_ptr<Mesh> GetMesh() { return m_mesh; };
	inline XMMATRIX& GetWorld() { return m_world; };

private:
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Texture> m_texture;

	XMMATRIX m_world;

	// Transformations with some standard values.
	float m_posX = 0.0f, m_posY = 0.0f, m_posZ = 0.0f;
	float m_rotX = 0.0f, m_rotY = 0.0f, m_rotZ = 0.0f;
	float m_scaleX = 1.0f, m_scaleY = 1.0f, m_scaleZ = 1.0f;
	XMMATRIX m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_translation;
	XMMATRIX m_scale;
};

