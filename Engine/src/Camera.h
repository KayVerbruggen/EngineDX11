#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include "Util.h"

using namespace DirectX;

class Camera
{
public:
	Camera();
	~Camera();

	void Update(float deltaTime);

	inline XMMATRIX GetView() const { return view; };
	inline XMMATRIX GetProjection() const { return projection; };

private:
	XMMATRIX wvp, world, view, projection, rotationMatrix;
	XMVECTOR pos, target, up;
	XMVECTOR defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	float camYaw = 0.0f;
	float camPitch = 0.0f;
	float fov = 90.0f;

	// TODO: Move the movement code out of the engine.
	// Variables for movement.
	bool m_useCursor = false;
	POINT prevMousePos = { (LONG)SCREEN_WIDTH / 2, (LONG)SCREEN_HEIGHT / 2 };
	POINT currMousePos = { (LONG)SCREEN_WIDTH / 2, (LONG)SCREEN_HEIGHT / 2 };
	float mouseSens = 5.0f;
	float movementSpeed = 2.5f;
};

