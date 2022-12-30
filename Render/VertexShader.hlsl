
cbuffer VSConstantBuffer : register(b0)
{
	matrix transform_localToWorld;
	matrix transform_worldToCamera;
	matrix transform_cameraToProjected;

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
};
VertexOut main(VertexIn input)
{
	VertexOut output;
	float3 i_vertexPosition_local = input.pos;
	float4 vertexPosition_local = float4(i_vertexPosition_local, 1.0);

	float4 vertexPosition_world = mul(transform_localToWorld,vertexPosition_local);
	
    float4 vertexPosition_camera = mul(transform_worldToCamera, vertexPosition_world);
		
	float4 vertexPosition_projected = mul(transform_cameraToProjected, vertexPosition_camera);
	output.pos = vertexPosition_projected / vertexPosition_projected[3];
	output.uv = input.uv;
	output.nml = input.nml;
	return output;
}