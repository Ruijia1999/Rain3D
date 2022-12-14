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

Rain::MeshRender::MeshRenderSystem::MeshRenderSystem() {

}