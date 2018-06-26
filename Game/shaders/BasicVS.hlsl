cbuffer cbPerObject
{
	float4x4 world;
	float4x4 view;
	float4x4 projection;
};

struct InputVS
{
	float3 position : POSITION;
	float3 normal : NORMAL;
};

struct OutputVS
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
};

OutputVS main(InputVS input)
{
	OutputVS output;

	output.position = mul(float4(input.position, 1.0), mul(world, mul(view, projection)));
	output.normal = mul(input.normal, world);

	return output;
}