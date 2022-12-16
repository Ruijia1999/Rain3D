#include "RenderData.h"
Rain::Render::RenderData::RenderData() {
	mesh = nullptr;
	effect = nullptr;
}
Rain::Render::RenderData::RenderData(const Mesh* i_mesh, const Effect* i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer) {
	mesh = i_mesh;
	effect = i_effect;
	constantBuffer = i_constantBuffer;
}