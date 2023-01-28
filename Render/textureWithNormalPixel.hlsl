Texture2D colorMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState colorSampler: register(s0);
SamplerState normalSampler: register(s1);
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
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
	float3 tan:TEXCOORD2;
	float4 color:COLOR;
};

float3 NormalSampleToWorldSpace(float3 normalMapSample,
	float3 unitNormalW,
	float3 tangentW)
{

	float3 normalT = 2.0f * normalMapSample - 1.0f;


	float3 N = unitNormalW;
	float3 T = normalize(tangentW - dot(tangentW, N) * N);
	float3 B = cross(N, T);

	float3x3 TBN = float3x3(T, B, N);


	float3 bumpedNormalW = mul(normalT, TBN);

	return bumpedNormalW;
}
float4 main(VertexOut input) : SV_TARGET
{

    float4 col = colorMap.Sample(colorSampler, input.uv);
	float3 normalSample = normalMap.Sample(normalSampler, input.uv);
	float3 unitNormal = normalize(input.nml);
	float3 unitTangent = normalize(input.tan);
	float3 normal = NormalSampleToWorldSpace(normalSample, unitNormal, unitTangent);
	float rate = 0.3 + max(0, dot(-1 * normal, lightDirection)) * 0.7;
	return float4(rate* col[0], rate * col[1], rate * col[2], input.color[3]);
}

