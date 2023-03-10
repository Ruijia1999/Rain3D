#include "RenderData.h"
Rain::Render::RenderData::RenderData() {
}
Rain::Render::RenderData::RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> i_normalMap, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer) :
	RenderDataBase(RenderDataType::StaticMesh),
	mesh(i_mesh),
	effect(i_effect),
	texture(i_texture),
	normalMap(i_normalMap),
	constantBuffer(i_constantBuffer)
{

}

Rain::Render::RenderData::RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> i_normalMap, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer, const ConstantBufferFormats::FrameConstantBuffer& i_frameBuffer) :
	RenderDataBase(RenderDataType::StaticMesh),
	mesh(i_mesh),
	effect(i_effect),
	texture(i_texture),
	normalMap(i_normalMap),
	constantBuffer(i_constantBuffer),
	frameBuffer(i_frameBuffer)
{

}
Rain::Render::RenderData::~RenderData() {
	int j = 0;
}

void Rain::Render::RenderData::Draw() {
	effect->Bind();
	if (texture != nullptr) {
		texture->Draw(0);
	}
	if (normalMap != nullptr) {
		normalMap->Draw(1);
	}
	mesh->Draw();
}