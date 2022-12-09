#include "ConstantBuffer.h"

Rain::Render::ConstantBuffer::VSConstantBuffer::VSConstantBuffer(){
	int j = 90;
}

Rain::Render::ConstantBuffer::VSConstantBuffer& Rain::Render::ConstantBuffer::VSConstantBuffer::operator=(const VSConstantBuffer& i_constantBuffer) {
	if (this != &i_constantBuffer) {
		transform_localToWorld = i_constantBuffer.transform_localToWorld;
		transform_worldToCamera = i_constantBuffer.transform_worldToCamera;
		transform_cameraToProjected = i_constantBuffer.transform_cameraToProjected;
	}

	return *this;
}

Rain::Render::ConstantBuffer::VSConstantBuffer::VSConstantBuffer(const VSConstantBuffer& i_constantBuffer) {
	transform_localToWorld = i_constantBuffer.transform_localToWorld;
	transform_worldToCamera = i_constantBuffer.transform_worldToCamera;
	transform_cameraToProjected = i_constantBuffer.transform_cameraToProjected;
}