#pragma once

#include <DirectXMath.h>
using namespace DirectX;

struct Light
{
	Light();
	~Light();

	XMFLOAT3 dir;
	float pad;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
};