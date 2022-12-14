#include "GameObjectComponent.h"

Rain::GameObject::GameObjectComponent::GameObjectComponent():ComponentBase(0) {
	isActive = true;
	isVisible = true;
	parent = nullptr;
}

Rain::GameObject::GameObjectComponent::GameObjectComponent(int i_id) :ComponentBase(i_id) {
	isActive = true;
	isVisible = true;
	parent = nullptr;
}
Rain::GameObject::GameObjectComponent::GameObjectComponent(int i_id, bool i_isActive, bool i_isVisible, const char* i_name, const char* i_tag) {
	id = i_id;
	isActive = i_isActive;
	isVisible = i_isVisible;
	name = i_name;
	tag = i_tag;
	parent = nullptr;
}
void Rain::GameObject::GameObjectComponent::Initialize() {

}
void Rain::GameObject::GameObjectComponent::Update(uint64_t i_timeSinceLastFrame) {

}
void Rain::GameObject::GameObjectComponent::Destroy() {

}