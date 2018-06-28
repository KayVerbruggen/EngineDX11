#include "Camera.h"

enum Keys : WPARAM
{
	A = 0x41, B, C, D, E, F, G,
	H, I, J, K, L, M, N, O, P, Q,
	R, S, T, U, V, W, X, Y, Z
};

Camera::Camera()
{
	pos		= XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
	target	= XMVectorSet(0.0f, 0.0f,  1.0f, 0.0f);
	up		= XMVectorSet(0.0f, 1.0f,  0.0f, 0.0f);

	view = XMMatrixLookAtLH(pos, target, up);

	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

	world = XMMatrixIdentity();
	wvp = world * view * projection;
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	if (GetAsyncKeyState(C) & 1) 
	{
		SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		m_useCursor = !m_useCursor;
		ShowCursor(m_useCursor);
	}

	if (!m_useCursor) 
	{
		float movementForward = 0.0f;
		float movementHorizontal = 0.0f;

		if (GetAsyncKeyState(W))
		{
			movementForward = movementSpeed * deltaTime;
		}
		if (GetAsyncKeyState(S))
		{
			movementForward = -movementSpeed * deltaTime;
		}
		if (GetAsyncKeyState(A))
		{
			movementHorizontal = -movementSpeed * deltaTime;
		}
		if (GetAsyncKeyState(D))
		{
			movementHorizontal = movementSpeed * deltaTime;
		}

		GetCursorPos(&currMousePos);

		if (currMousePos.x != prevMousePos.x)
		{
			camYaw += (currMousePos.x - prevMousePos.x) * (mouseSens / 100.0f);
		}
		if (currMousePos.y != prevMousePos.y)
		{
			camPitch += (currMousePos.y - prevMousePos.y) * (mouseSens / 100.0f);

			if (camPitch > 90.0f)
				camPitch = 90.0f;

			if (camPitch < -90.0f)
				camPitch = -90.0f;
		}

		rotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(camPitch), XMConvertToRadians(camYaw), 0);
		target = XMVector3TransformCoord(defaultForward, rotationMatrix);
		target = XMVector3Normalize(target);

		XMMATRIX rotateYTempMatrix;
		rotateYTempMatrix = XMMatrixRotationY(XMConvertToRadians(camYaw));

		XMVECTOR camRight = XMVector3TransformCoord(defaultRight, rotateYTempMatrix);
		up = XMVector3TransformCoord(up, rotateYTempMatrix);
		XMVECTOR camForward = XMVector3TransformCoord(defaultForward, rotateYTempMatrix);

		pos += movementHorizontal * camRight;
		pos += movementForward * camForward;

		target = pos + target;
		view = XMMatrixLookAtLH(pos, target, up);
	
		SetCursorPos(prevMousePos.x, prevMousePos.y);
	}
}