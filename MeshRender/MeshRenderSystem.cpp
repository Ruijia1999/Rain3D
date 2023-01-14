#include "MeshRenderSystem.h"
Rain::MeshRender::MeshRenderSystem* Rain::MeshRender::MeshRenderSystem::instance;

Rain::MeshRender::MeshRenderSystem* Rain::MeshRender::MeshRenderSystem::GetInstance() {
	if (instance == nullptr) {
		instance = new MeshRenderSystem();
		return instance;
	}
	else {
		return instance;
	}
}
Rain::Render::Mesh* Rain::MeshRender::MeshRenderSystem::InitializeMesh(const char* i_name) {
	Render::Mesh* mesh = new Render::Mesh();
	meshes.insert(std::pair<std::string, Render::Mesh*>(i_name, mesh));
	mesh->Initialize(i_name);
	return mesh;
}
void Rain::MeshRender::MeshRenderSystem::Initialize() {
	SystemBase::Initialize();
	
	effects.insert(std::pair<std::string, Render::Effect*>("default", new Render::Effect()));
	effects.find("default")->second->Initialize("VertexShader", "PixelShader");
	effects.insert(std::pair<std::string, Render::Effect*>("red", new Render::Effect()));
	effects.find("red")->second->Initialize("VertexShader", "red");
}

Rain::MeshRender::MeshRenderSystem::MeshRenderSystem() {

}