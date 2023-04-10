Texture2D colorMap : register(t0);
SamplerState colorSampler: register(s0);

cbuffer VSConstantBuffer : register(b0)
{
	matrix transform_localToWorld;
	matrix transform_worldToCamera;
	matrix transform_cameraToProjected;
	float4 color;
}
cbuffer frameConstantBuffer : register(b1)
{

	float time;
	float3 lightDirection;
	float3 cameraPos;
	float3 cameraForward;
	float4 lightColor;

}
struct VertexOut {
	float4 pos:SV_POSITION;
	float3 nml:TEXCOORD1;
	float4 color:COLOR;
};

float4 main(VertexOut input) : SV_TARGET
{
	float3 nml = normalize(input.nml);
	float rate = 0.3 + max(0, dot(-1 * nml, lightDirection)) * 0.7;

	return float4(rate* input.color[0], rate * input.color[1], rate * input.color[2], input.color[3]);
}