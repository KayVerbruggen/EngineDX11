#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class Light
{
public:
	Light();
	Light(float dirX, float dirY, float dirZ);
	~Light();

private:
	XMFLOAT3 dir;
	float pad;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
};