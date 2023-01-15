#include "RenderData.h"
Rain::Render::RenderData::RenderData() {
}
Rain::Render::RenderData::RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer):
	mesh(i_mesh),
    effect(i_effect),
    constantBuffer(i_constantBuffer)
{
	int j = 0;
}
Rain::Render::RenderData::~RenderData() {
	int j = 0;
}