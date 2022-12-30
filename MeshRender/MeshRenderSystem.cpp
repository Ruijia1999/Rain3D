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

void Rain::MeshRender::MeshRenderSystem::Initialize() {
	SystemBase::Initialize();
	meshes.insert(std::pair<std::string, Render::Mesh*>("box.hrj", new Render::Mesh()));
	meshes.find("box.hrj")->second->Initialize("box.hrj");
	meshes.insert(std::pair<std::string, Render::Mesh*>("house.hrj", new Render::Mesh()));
	meshes.find("house.hrj")->second->Initialize("house.hrj");
	meshes.insert(std::pair<std::string, Render::Mesh*>("ss.hrj", new Render::Mesh()));
	meshes.find("ss.hrj")->second->Initialize("ss.hrj");
	meshes.insert(std::pair<std::string, Render::Mesh*>("cube.hrj", new Render::Mesh()));
	meshes.find("cube.hrj")->second->Initialize("cube.hrj");
	effects.insert(std::pair<std::string, Render::Effect*>("default", new Render::Effect()));
	effects.find("default")->second->Initialize("vertexShader", "pixelShader");
}

Rain::MeshRender::MeshRenderSystem::MeshRenderSystem() {

}