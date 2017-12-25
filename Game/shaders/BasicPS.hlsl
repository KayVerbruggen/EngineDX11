struct InputPS
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;
};

float centerX = 640.0f;
float centerY = 360.0f;

float4 vignettePass(float4 vignettePixelPos, float4 color)
{
	if (vignettePixelPos.x < centerX)
	{
		vignettePixelPos.x = -(vignettePixelPos.x / 1280.0);
	}
	else
	{
		vignettePixelPos.x = vignettePixelPos.x / 1280.0;
	}
	if (vignettePixelPos.y < centerY)
	{
		vignettePixelPos.y = -(vignettePixelPos.y / 720.0);
	}
	else
	{
		vignettePixelPos.y = vignettePixelPos.y / 720.0;
	}

	float2 dist = vignettePixelPos - 0.5;
	dist.x = 1 - dot(dist, dist);
	color.a -= max(1.0f - saturate(pow(dist.x, 2.0f)), 0.1);

	return color;
}

float4 main(InputPS input) : SV_TARGET
{
	return vignettePass(input.position, input.color);
}