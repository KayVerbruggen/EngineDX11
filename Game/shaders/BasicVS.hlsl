cbuffer cbPerObject
{
	float4x4 wvp;
	float4x4 world;
};

struct InputVS
{
	float3 position : POSITION;
	float2 texCoord	: TEXCOORD;
	float3 normal : NORMAL;
};

struct OutputVS
{
	float4 position : SV_POSITION;
	float2 texCoord	: TEXCOORD;
	float3 normal : NORMAL;
};

OutputVS main( InputVS input)
{
	OutputVS output;

	output.position = mul(float4(input.position.x, input.position.y, input.position.z, 1), wvp);
	output.texCoord = input.texCoord;
	output.normal = mul(input.normal, world);

	return output;
}