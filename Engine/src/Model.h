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

	std::shared_ptr<Texture> GetTexture() { return m_texture; };
	std::shared_ptr<Mesh> GetMesh() { return m_mesh; };
	inline XMMATRIX& GetWorld() { return m_world; };

private:
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Texture> m_texture;

	XMMATRIX m_world;

	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
	XMMATRIX m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_translation;

};

