struct InputPS
{
	float4 position  : SV_POSITION;
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

float4 main(InputPS input) : SV_TARGET
{
	input.normal = normalize(input.normal);
	
	float4 diffuse = { 1.0f, 0.3f, 0.8f, 1.0f };

	float3 lightDir = normalize(-light.dir);
	float lightIntensity = saturate(dot(input.normal, lightDir));
	float4 color = saturate(light.diffuse * lightIntensity);

	color = color * diffuse;

	return color;
}