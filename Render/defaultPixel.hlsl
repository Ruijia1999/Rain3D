struct VertexOut {
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};
float4 main(VertexOut input) : SV_TARGET
{
	return input.color;
}