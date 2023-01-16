
cbuffer VSConstantBuffer : register(b0)
{
	matrix transform_localToWorld;
	matrix transform_worldToCamera;
	matrix transform_cameraToProjected;
	float4 color;
}

struct VertexIn {
	float3 pos:POSITION;
	float3 nml:NORMAL;
	float2 uv:TEXCOORD0;
};
struct VertexOut {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
	float4 color:COLOR;
};
Texture2D colorMap : register(t0);
SamplerState colorSampler: register(s0);

VertexOut main(VertexIn input)
{
	VertexOut output;
	//position
	float3 i_vertexPosition_local = input.pos;
	float4 vertexPosition_local = float4(i_vertexPosition_local, 1.0);

	float4 vertexPosition_world = mul(transform_localToWorld,vertexPosition_local);
	
    float4 vertexPosition_camera = mul(transform_worldToCamera, vertexPosition_world);
		
	float4 vertexPosition_projected = mul(transform_cameraToProjected, vertexPosition_camera);
	//normal
	float4 normal_local = float4(input.nml, 0.0);

	float4 normal_world = mul(transform_localToWorld, normal_local);

	output.pos = vertexPosition_projected / vertexPosition_projected[3];
	output.uv = float2(input.uv[0],1-input.uv[1]);
	output.nml = float3(normal_world[0], normal_world[1], normal_world[2]) ;
	output.color = color;
	return output;
}