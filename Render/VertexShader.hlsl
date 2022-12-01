
cbuffer VSConstantBuffer : register(b0)
{
	matrix transform_localToWorld;
	matrix transform_worldToCamera;
	matrix transform_cameraToProjected;

}

float4 main( float3 i_vertexPosition_local : POSITION ) : SV_POSITION
{
	
	
	float4 vertexPosition_local = float4(i_vertexPosition_local, 1.0);

	float4 vertexPosition_world = mul(transform_localToWorld,vertexPosition_local);
	
    float4 vertexPosition_camera = mul(transform_worldToCamera, vertexPosition_world);
		
	float4 vertexPosition_projected = mul(transform_cameraToProjected, vertexPosition_camera);
	
	return vertexPosition_projected/ vertexPosition_projected[3];
}