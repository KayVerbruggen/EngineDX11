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

	XMMATRIX wvp, world, camView, camProjection, camRotationMatrix;
	XMVECTOR camPos, camTarget, camUp;
	XMVECTOR defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	float camYaw = 0.0f;
	float camPitch = 0.0f;

	// Variables for movement.
	POINT prevMousePos = { (LONG)SCREEN_WIDTH / 2, (LONG)SCREEN_HEIGHT / 2 };
	POINT currMousePos = { (LONG)SCREEN_WIDTH / 2, (LONG)SCREEN_HEIGHT / 2 };
	float mouseSens = 5.0f;
	float movementHorizontal, movementForward;
	float movementSpeed = 2.5f;
};

