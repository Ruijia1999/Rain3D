#include "ConstantBuffer.h"

Rain::Render::ConstantBuffer::VSConstantBuffer::VSConstantBuffer(){}

const Rain::Render::ConstantBuffer::VSConstantBuffer& Rain::Render::ConstantBuffer::VSConstantBuffer::operator=(const VSConstantBuffer& i_constantBuffer) {
	Rain::Render::ConstantBuffer::VSConstantBuffer constantbuffer;
	constantbuffer.transform_localToWorld = i_constantBuffer.transform_localToWorld;
	constantbuffer.transform_worldToCamera = i_constantBuffer.transform_localToWorld;
	constantbuffer.transform_cameraToProjected = i_constantBuffer.transform_localToWorld;
	return constantbuffer;
}

Rain::Render::ConstantBuffer::VSConstantBuffer::VSConstantBuffer(const VSConstantBuffer& i_constantBuffer) {

}