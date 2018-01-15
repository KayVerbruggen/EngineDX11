#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include "Util.h"

using namespace DirectX;

class Camera
{
public:
	Camera(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext);
	~Camera();

	void Update(float deltaTime);
	XMMATRIX GetWVP();
	void SetWorld(const XMMATRIX& localWorld);

private:
	HRESULT hr;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceCon;

	XMMATRIX wvp, world, camView, camProjection;
	XMVECTOR camPos, camTarget, camUp;
	XMMATRIX camYaw, camPitch;

	// Variables for movement.
	POINT prevMousePos = { (LONG)SCREEN_WIDTH / 2, (LONG)SCREEN_HEIGHT / 2 };
	POINT currMousePos = { (LONG)SCREEN_WIDTH / 2, (LONG)SCREEN_HEIGHT / 2 };
	float mouseSens = 0.5f;
	float movementSpeed = 0.1f;
};

