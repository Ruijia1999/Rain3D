struct VertexOut {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
};
float4 main(VertexOut input) : SV_TARGET
{
	float rate = mul(input.nml,float3(0,0,1));
	return rate*float4(1.0f, 1.0f, 1.0f, 1.0f);
}