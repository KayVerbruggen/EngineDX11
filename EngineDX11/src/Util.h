#pragma once

#include <DirectXMath.h>

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

// TODO: What if one of these changes? How do we handle that.
// Should we re-create the Device if this changes?
const float SCREEN_WIDTH	= 1280.0f;
const float SCREEN_HEIGHT	= 720.0f;
const bool	V_SYNC			= true;
const bool	FULLSCREEN		= false;
const float REFRESH_RATE	= 60.0f;
const UINT	MSAA			= 1;