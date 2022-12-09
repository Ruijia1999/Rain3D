#include "RenderData.h"
Rain::Render::RenderData::RenderData() {
	mesh = nullptr;
	effect = nullptr;
}
Rain::Render::RenderData::RenderData(Mesh* i_mesh, Effect* i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer) {
	mesh = i_mesh;
	effect = i_effect;
	constantBuffer = i_constantBuffer;
}