#include "RenderData.h"
Rain::Render::RenderData::RenderData() {
}
Rain::Render::RenderData::RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> i_normalMap, const ConstantBuffer::VSConstantBuffer i_constantBuffer) :
	mesh(i_mesh),
	effect(i_effect),
	texture(i_texture),
	normalMap(i_normalMap),
	constantBuffer(i_constantBuffer)
{
	int j = 0;
}
Rain::Render::RenderData::RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> i_normalMap, const ConstantBuffer::VSConstantBuffer i_constantBuffer, const ConstantBuffer::WaterConstantBuffer i_waterconstantBuffer):
	mesh(i_mesh),
    effect(i_effect),
	texture(i_texture),
	normalMap(i_normalMap),
    constantBuffer(i_constantBuffer),
	waterBuffer(i_waterconstantBuffer)
{
	int j = 0;
}
Rain::Render::RenderData::~RenderData() {
	int j = 0;
}