Texture2D colorMap : register(t0);
SamplerState colorSampler: register(s0);
SamplerState normalSampler: register(s1);
cbuffer VSConstantBuffer : register(b0)
{
	matrix transform_localToWorld;
	matrix transform_worldToCamera;
	matrix transform_cameraToProjected;
	float4 color;
}
struct VertexOut {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
	float4 color:COLOR;
};
float4 main(VertexOut input) : SV_TARGET
{
	float rate = 0.3 + max(0, dot(-1 * input.nml, float3(0.5, -0.707, 0.5))) * 0.7;
    float4 col = colorMap.Sample(colorSampler, input.uv);
	return float4(rate* col[0], rate * col[1], rate * col[2],1);
}