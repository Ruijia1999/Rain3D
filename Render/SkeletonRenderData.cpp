#include "SkeletonRenderData.h"

Rain::Render::SkeletonRenderData::SkeletonRenderData() {
}
Rain::Render::SkeletonRenderData::SkeletonRenderData(const std::shared_ptr<SkeletalMesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer, const ConstantBufferFormats::FrameConstantBuffer& i_frameBuffer) :
	RenderDataBase(RenderDataType::SkeletalMesh),
	constantBuffer(i_constantBuffer),
	frameBuffer(i_frameBuffer),
	effect(i_effect),
	mesh(i_mesh)
{
	int j;
}

//Rain::Render::SkeletonRenderData::SkeletonRenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> i_normalMap, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer, const ConstantBufferFormats::FrameConstantBuffer& i_frameBuffer) :
//	SkeletonRenderDataBase(SkeletonRenderDataType::StaticMesh),
//	mesh(i_mesh),
//	effect(i_effect),
//	texture(i_texture),
//	normalMap(i_normalMap),
//	constantBuffer(i_constantBuffer),
//	frameBuffer(i_frameBuffer)
//{
//
//}
Rain::Render::SkeletonRenderData::~SkeletonRenderData() {
	int j = 0;
}

void Rain::Render::SkeletonRenderData::Draw() {
	effect->Bind();
	if (texture != nullptr) {
		texture->Draw(0);
	}
	if (normalMap != nullptr) {
		normalMap->Draw(1);
	}
	mesh->UpdateMesh();
	mesh->Draw();
}