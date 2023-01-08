#include "MeshRenderComponent.h"
Rain::MeshRender::MeshRenderComponent::MeshRenderComponent() {
	id = 0;
	mesh = nullptr;
	effect = nullptr;
}
Rain::MeshRender::MeshRenderComponent::MeshRenderComponent(int i_id, const Render::Mesh* i_mesh, const Render::Effect* i_effect, Math::Vector4 i_color) {
	id = i_id;
	mesh = i_mesh;
	effect = i_effect;
	color = i_color;
}
void Rain::MeshRender::MeshRenderComponent::Initialize() {

}
void Rain::MeshRender::MeshRenderComponent::Update(uint64_t i_timeSinceLastFrame) {

}
void Rain::MeshRender::MeshRenderComponent::Destroy() {

}