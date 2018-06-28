#include "Light.h"

Light::Light()
{
}

Light::Light(float dirX, float dirY, float dirZ)
{
	ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	dir = XMFLOAT3(dirX, dirY, dirZ);
}

Light::~Light()
{
}