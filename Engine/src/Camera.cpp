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

	camProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(103.0f), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

	world = XMMatrixIdentity();
	wvp = world * camView * camProjection;
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	if (GetAsyncKeyState(W))
	{
		camPos += XMVectorSet(0.0f, 0.0f, movementSpeed, 0.0f);
	}
	if (GetAsyncKeyState(S))
	{
		camPos -= XMVectorSet(0.0f, 0.0f, movementSpeed, 0.0f);
	}
	if (GetAsyncKeyState(A))
	{
		camPos -= XMVectorSet(movementSpeed, 0.0f, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState(D))
	{
		camPos += XMVectorSet(movementSpeed, 0.0f, 0.0f, 0.0f);
	}

	GetCursorPos(&currMousePos);
	
	if (currMousePos.x - prevMousePos.x != 0)
	{

	}
	if (currMousePos.y - prevMousePos.y != 0)
	{

	}

	camTarget = camPos + XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
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