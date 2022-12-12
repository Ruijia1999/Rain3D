#include "GameObjectSystem.h"
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

Rain::GameObject::GameObjectSystem::GameObjectSystem(){

}