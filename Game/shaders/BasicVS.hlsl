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

	output.position = float4(input.position.x, input.position.y, input.position.z, 1);
	if (output.position.x > 0)
	{
		output.position.y *= 1.25;
	}
	else 
	{
		output.position.y *= 0.75;
	}
	output.color = input.color;

	return output;
}