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
std::shared_ptr<Rain::Render::Mesh> Rain::MeshRender::MeshRenderSystem::InitializeMesh(const char* i_name) {
	Render::Mesh* mesh = new Render::Mesh();
	meshes.insert(std::pair<std::string, Render::Mesh*>(i_name, mesh));
	mesh->Initialize(i_name);
	return meshes.find(i_name)->second;
}

std::shared_ptr<Rain::Render::Texture> Rain::MeshRender::MeshRenderSystem::InitializeTexture(const char* i_name) {
	if (strcmp(i_name,"")==0) {
		return nullptr;
	}
	Render::Texture* texture = new Render::Texture();
	textures.insert(std::pair<std::string, Render::Texture*>(i_name, texture));
	texture->Initialize(i_name);
	return textures.find(i_name)->second;
}
void Rain::MeshRender::MeshRenderSystem::Initialize() {
	SystemBase::Initialize();
	
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("default", new Render::Effect()));
	effects.find("default")->second->Initialize("VertexShader", "PixelShader");
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("red", new Render::Effect()));
	effects.find("red")->second->Initialize("VertexShader", "red");
}

Rain::MeshRender::MeshRenderSystem::MeshRenderSystem() {

}