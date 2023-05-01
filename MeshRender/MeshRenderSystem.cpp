#include "MeshRenderSystem.h"
#include "EngineLog\EngineLog.h"
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
std::shared_ptr<Rain::Render::SkeletalMesh> Rain::MeshRender::MeshRenderSystem::InitializeSkeletalMesh(const char* i_name) {
	Render::SkeletalMesh* mesh = new Render::SkeletalMesh();
	skeletalMeshes.insert(std::pair<std::string, Render::SkeletalMesh*>(i_name, mesh));
	mesh->Initialize(i_name);
	return skeletalMeshes.find(i_name)->second;
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
	Render::ConstantLayout::Initialize();
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("default", new Render::Effect()));
	effects.find("default")->second->Initialize("defaultVertex", "defaultPixel", Render::ConstantLayout::staticMeshLayout, Render::ConstantLayout::staticMeshEleNum);
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("texture", new Render::Effect()));
	effects.find("texture")->second->Initialize("textureVertex", "texturePixel", Render::ConstantLayout::staticMeshLayout, Render::ConstantLayout::staticMeshEleNum);
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("textureWithNormal", new Render::Effect()));
	effects.find("textureWithNormal")->second->Initialize("textureWithNormalVertex", "textureWithNormalPixel", Render::ConstantLayout::staticMeshLayout, Render::ConstantLayout::staticMeshEleNum);
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("water", new Render::Effect()));
	effects.find("water")->second->Initialize("waterVertex", "waterPixel", Render::ConstantLayout::staticMeshLayout, Render::ConstantLayout::staticMeshEleNum);
	effects.insert(std::pair<std::string, std::shared_ptr<Render::Effect>>("defaultWithNormal", new Render::Effect()));
	effects.find("defaultWithNormal")->second->Initialize("defaultWithNormalVertex", "defaultWithNormalPixel", Render::ConstantLayout::skeletalMeshLayout, Render::ConstantLayout::skeletalMeshEleNum);
	EngineLog::Log("MeshRender System is initialized successfully.");
}

Rain::MeshRender::MeshRenderSystem::MeshRenderSystem() {

}