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
	Model(Mesh mesh, Texture texture);
	~Model();

	void SetPosition(float x, float y, float z);
	void AddPosition(float x, float y, float z);
	
	void SetRotation(float x, float y, float z);
	void AddRotation(float x, float y, float z);

	Texture GetTexture() { return m_texture; };
	Mesh GetMesh() { return m_mesh; };
	inline XMMATRIX GetWorld() const { return m_world; };

private:
	Mesh m_mesh;
	Texture m_texture;

	XMMATRIX m_world;

	float m_posX, m_posY, m_posZ;
	float m_rotX, m_rotY, m_rotZ;
	XMMATRIX m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_translation;

};

