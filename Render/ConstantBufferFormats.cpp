#include "ConstantBufferFormats.h"

Rain::Render::ConstantBufferFormats::VSConstantBuffer::VSConstantBuffer() {
	int j = 90;
}

Rain::Render::ConstantBufferFormats::VSConstantBuffer& Rain::Render::ConstantBufferFormats::VSConstantBuffer::operator=(const VSConstantBuffer& i_constantBuffer) {
	if (this != &i_constantBuffer) {
		transform_localToWorld = i_constantBuffer.transform_localToWorld;
		transform_worldToCamera = i_constantBuffer.transform_worldToCamera;
		transform_cameraToProjected = i_constantBuffer.transform_cameraToProjected;
		color = i_constantBuffer.color;
	}

	return *this;
}

Rain::Render::ConstantBufferFormats::FrameConstantBuffer::FrameConstantBuffer() {

}

Rain::Render::ConstantBufferFormats::VSConstantBuffer::VSConstantBuffer(const VSConstantBuffer& i_constantBuffer) {
	transform_localToWorld = i_constantBuffer.transform_localToWorld;
	transform_worldToCamera = i_constantBuffer.transform_worldToCamera;
	transform_cameraToProjected = i_constantBuffer.transform_cameraToProjected;
	color = i_constantBuffer.color;
}

Rain::Render::ConstantBufferFormats::FrameConstantBuffer::FrameConstantBuffer(const FrameConstantBuffer& i_constantBuffer) {
	time = i_constantBuffer.time;
	lightDirection = i_constantBuffer.lightDirection;
	cameraPos = i_constantBuffer.cameraPos;
	cameraForward = i_constantBuffer.cameraForward;
	lightColor = i_constantBuffer.lightColor;
}

Rain::Render::ConstantBufferFormats::FrameConstantBuffer& Rain::Render::ConstantBufferFormats::FrameConstantBuffer::operator=(const FrameConstantBuffer& i_constantBuffer) {
	if (this != &i_constantBuffer) {
		time = i_constantBuffer.time;
		lightDirection = i_constantBuffer.lightDirection;
		cameraPos = i_constantBuffer.cameraPos;
		cameraForward = i_constantBuffer.cameraForward;
		lightColor = i_constantBuffer.lightColor;
	}

	return *this;
}
