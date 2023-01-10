struct VertexOut {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
	float4 color:COLOR;
};
float4 main(VertexOut input) : SV_TARGET
{
	float rate = 0.3+max(0, dot(-1 * input.nml, float3(-0.5, -0.707, 0.5)))*0.7;
	return float4(rate*input.color[0], rate * input.color[1], rate * input.color[2],1);
}