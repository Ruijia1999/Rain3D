struct VertexOut {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
};
float4 main(VertexOut input) : SV_TARGET
{
	float rate = 0.3+max(0,dot(-1*input.nml,float3(0.5,0.707,0.5)))*0.7;
	return rate*float4(1.0f, 1.0f, 1.0f, 1.0f);
}