struct InputPS
{
	float4 position  : SV_POSITION;
	float2 texCoord : TEXCOORDS;
	float3 normal : NORMAL;
};

struct Light
{
	float3 dir;
	float4 ambient;
	float4 diffuse;
};

cbuffer cbPerFrame
{
	Light light;
};

Texture2D objTexture;
SamplerState objSamplerState;

float centerX = 960.0f;
float centerY = 540.0f;

float4 vignettePass(float4 vignettePixelPos, float4 color)
{
	if (vignettePixelPos.x < centerX)
	{
		vignettePixelPos.x = -(vignettePixelPos.x / 1920.0);
	}
	else
	{
		vignettePixelPos.x = vignettePixelPos.x / 1920.0;
	}
	if (vignettePixelPos.y < centerY)
	{
		vignettePixelPos.y = -(vignettePixelPos.y / 1080.0);
	}
	else
	{
		vignettePixelPos.y = vignettePixelPos.y / 1080.0;
	}

	float2 dist = vignettePixelPos - 0.5f;
	dist.x = 1 - dot(dist, dist);
	color.a -= 1.0f - saturate(pow(dist.x, 5.5f));

	return color;
}

float4 main(InputPS input) : SV_TARGET
{
	input.normal = normalize(input.normal);
	
	// return vignettePass(input.position, input.color);
	float4 diffuse = objTexture.Sample(objSamplerState, input.texCoord);

	float3 finalColor;

	finalColor = diffuse * light.ambient;
	finalColor += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);

	return float4(finalColor, diffuse.a);
}