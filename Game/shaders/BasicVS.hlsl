cbuffer cbPerObject
{
	float4x4 wvp;
};

struct InputVS
{
	float3 position : POSITION;
	float4 color	: COLOR;
};

struct OutputVS
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;
};

OutputVS main( InputVS input)
{
	OutputVS output;

	output.position = mul(float4(input.position.x, input.position.y, input.position.z, 1), wvp);
	output.color = input.color;

	return output;
}