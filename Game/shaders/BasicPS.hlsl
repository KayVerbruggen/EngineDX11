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
	float4 colorObj;
};

float4 main(InputPS input) : SV_TARGET
{
	input.normal = normalize(input.normal);

	float3 ambient = light.ambient.xyz * colorObj.xyz;

	float3 lightDir = normalize(-light.dir);
	float lightIntensity = max(dot(input.normal, lightDir), 0.0);
	float3 diffuse = light.diffuse.xyz * lightIntensity * colorObj;

	float3 color = ambient + diffuse;

	return float4(color, 1.0);
}