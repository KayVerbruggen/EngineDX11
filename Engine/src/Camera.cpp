#include "Camera.h"

enum Keys : WPARAM
{
	A = 0x41, B, C, D, E, F, G,
	H, I, J, K, L, M, N, O, P, Q,
	R, S, T, U, V, W, X, Y, Z
};

Camera::Camera(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext)
{
	m_device = Device;
	m_deviceCon = DeviceContext;

	camPos		= XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
	camTarget	= XMVectorSet(0.0f, 0.0f,  1.0f, 0.0f);
	camUp		= XMVectorSet(0.0f, 1.0f,  0.0f, 0.0f);

	camView = XMMatrixLookAtLH(camPos, camTarget, camUp);

	camProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

	world = XMMatrixIdentity();
	wvp = world * camView * camProjection;
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	movementForward = 0.0f;
	movementHorizontal = 0.0f;

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

	camRotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(camPitch), XMConvertToRadians(camYaw), 0);
	camTarget = XMVector3TransformCoord(defaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX rotateYTempMatrix;
	rotateYTempMatrix = XMMatrixRotationY(XMConvertToRadians(camYaw));

	camRight = XMVector3TransformCoord(defaultRight, rotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, rotateYTempMatrix);
	camForward = XMVector3TransformCoord(defaultForward, rotateYTempMatrix);

	camPos += movementHorizontal * camRight;
	camPos += movementForward * camForward;

	camTarget = camPos + camTarget;
	camView = XMMatrixLookAtLH(camPos, camTarget, camUp);
	
	SetCursorPos(prevMousePos.x, prevMousePos.y);
}

XMMATRIX Camera::GetWVP()
{
	return wvp;
}

void Camera::SetWorld(const XMMATRIX& localWorld)
{
	wvp = localWorld * camView * camProjection;
}