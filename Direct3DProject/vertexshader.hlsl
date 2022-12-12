cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};

OUTPUT main(float4 pos : POSITION, float4 color : COLOR)
{
	OUTPUT output = (OUTPUT)0;
	output.pos = mul( pos, World);
	output.pos = mul( output.pos, View);
	output.pos = mul( output.pos, Projection);
	output.color = color;
	return output;
}