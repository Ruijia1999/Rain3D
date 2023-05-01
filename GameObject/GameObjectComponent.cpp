#include "GameObjectComponent.h"

Rain::GameObject::GameObjectComponent::GameObjectComponent():ComponentBase(0,nullptr) {
	isActive = true;
	isVisible = true;
	parent = nullptr;
}

Rain::GameObject::GameObjectComponent::GameObjectComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity) :ComponentBase(i_id, i_entity) {
	isActive = true;
	isVisible = true;
	parent = nullptr;
}
Rain::GameObject::GameObjectComponent::GameObjectComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity, bool i_isActive, bool i_isVisible, const char* i_name, const char* i_tag) : ComponentBase(i_id, i_entity) {
	isActive = i_isActive;
	isVisible = i_isVisible;
	name = i_name;
	tag = i_tag;
	parent = nullptr;
}
void Rain::GameObject::GameObjectComponent::Initialize() {

}
void Rain::GameObject::GameObjectComponent::Update(double i_timeSinceLastFrame) {

}
void Rain::GameObject::GameObjectComponent::Destroy() {

}