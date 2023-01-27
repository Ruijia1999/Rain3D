#include "ConstantBuffer.h"

Rain::Render::ConstantBuffer::VSConstantBuffer::VSConstantBuffer(){
	int j = 90;
}

Rain::Render::ConstantBuffer::VSConstantBuffer& Rain::Render::ConstantBuffer::VSConstantBuffer::operator=(const VSConstantBuffer& i_constantBuffer) {
	if (this != &i_constantBuffer) {
		transform_localToWorld = i_constantBuffer.transform_localToWorld;
		transform_worldToCamera = i_constantBuffer.transform_worldToCamera;
		transform_cameraToProjected = i_constantBuffer.transform_cameraToProjected;
		color = i_constantBuffer.color;
	}

	return *this;
}

Rain::Render::ConstantBuffer::VSConstantBuffer::VSConstantBuffer(const VSConstantBuffer& i_constantBuffer) {
	transform_localToWorld = i_constantBuffer.transform_localToWorld;
	transform_worldToCamera = i_constantBuffer.transform_worldToCamera;
	transform_cameraToProjected = i_constantBuffer.transform_cameraToProjected;
	color = i_constantBuffer.color;
}

Rain::Render::ConstantBuffer::WaterConstantBuffer::WaterConstantBuffer() {
	int j = 90;
}

Rain::Render::ConstantBuffer::WaterConstantBuffer& Rain::Render::ConstantBuffer::WaterConstantBuffer::operator=(const WaterConstantBuffer& i_constantBuffer) {
	if (this != &i_constantBuffer) {
		speed = i_constantBuffer.speed;
		time = i_constantBuffer.time;
	}

	return *this;
}

Rain::Render::ConstantBuffer::WaterConstantBuffer::WaterConstantBuffer(const WaterConstantBuffer& i_constantBuffer) {
	speed = i_constantBuffer.speed;
	time = i_constantBuffer.time;
}