#pragma once

#include <DirectXMath.h>

struct Vertex
{
	float x, y, z;
	float u, v;
};

struct cbPerObject
{
	DirectX::XMMATRIX wvp;
};

// TODO: What if one of these changes? How do we handle that.
// Should we re-create the Device if this changes?
const float SCREEN_WIDTH	= 1920.0f;
const float SCREEN_HEIGHT	= 1080.0f;
const bool	V_SYNC			= true;
const bool	FULLSCREEN		= false;
const float REFRESH_RATE	= 60.0f;
const unsigned int	MSAA	= 1;		// Can't be higher than 8?