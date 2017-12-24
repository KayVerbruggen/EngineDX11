#pragma once

#include <DirectXMath.h>

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

const float SCREEN_WIDTH	= 1280.0f;
const float SCREEN_HEIGHT	= 720.0f;
const bool	V_SYNC			= true;
const bool	FULLSCREEN		= false;
const UINT	MSAA			= 1;