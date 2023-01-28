
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
struct VertexIn {
	float3 pos:POSITION;
	float3 nml:NORMAL;
	float3 tan:TANGENT;
	float2 uv:TEXCOORD0;
};
struct VertexOut {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
	float3 nml:TEXCOORD1;
	float3 tan:TEXCOORD2;
	float4 color:COLOR;
};
Texture2D colorMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState colorSampler: register(s0);
SamplerState normalSampler: register(s1);

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

	//tangent
	float4 tangent_local = float4(input.tan, 0.0);

	float4 tangent_world = mul(transform_localToWorld, tangent_local);
	float z = vertexPosition_projected[3];
	if (z < 0) {
		output.pos = vertexPosition_projected / (-1*vertexPosition_projected[3]);
	}
	else if (z > 0) {
		output.pos = vertexPosition_projected / vertexPosition_projected[3];
	}
	else {
		output.pos = float4(0, 0, 0, 1);
	}
	
	output.uv = float2(input.uv[0],1-input.uv[1]);
	output.nml = float3(normal_world[0], normal_world[1], normal_world[2]) ;
	output.tan = float3(tangent_world[0], tangent_world[1], tangent_world[2]);
	output.color = color;
	return output;
}