#include "GameObjectComponent.h"

Rain::GameObject::GameObjectComponent::GameObjectComponent():ComponentBase(0) {
	m_isActive = true;
	m_isVisible = true;
	m_parent = nullptr;
}

void Rain::GameObject::GameObjectComponent::Initialize() {

}
void Rain::GameObject::GameObjectComponent::Update(uint64_t i_timeSinceLastFrame) {

}
void Rain::GameObject::GameObjectComponent::Destroy() {

}