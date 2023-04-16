#include "GameObjectSystem.h"
#include "EngineLog\EngineLog.h"
Rain::GameObject::GameObjectSystem* Rain::GameObject::GameObjectSystem::instance;

Rain::GameObject::GameObjectSystem* Rain::GameObject::GameObjectSystem::GetInstance() {
	if (instance == nullptr) {
		instance = new GameObjectSystem();
		return instance;
	}
	else {
		return instance;
	}
}
int Rain::GameObject::GameObjectSystem::GetIDByName(const char* i_name) {
	for (auto object : m_componnets) {
		if (0 == strcmp(i_name, ((GameObject::GameObjectComponent*)object)->name)) {
			return object->id;
		}
	}
	return -1;
}
Rain::GameObject::GameObjectSystem::GameObjectSystem(){

}

void Rain::GameObject::GameObjectSystem::Initialize() {
	EngineLog::Log("Gameobject System is initialized successfully.");
}