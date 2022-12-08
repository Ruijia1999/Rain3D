#include "SystemBase.h"

Rain::ECS::SystemBase* Rain::ECS::SystemBase::GetInstance() {
	if (Instance == nullptr) {
		Instance = new SystemBase();
		return Instance;
	}
	else {
		return Instance;
	}
}
Rain::ECS::SystemBase::SystemBase() {

}

void Rain::ECS::SystemBase::Initialize() {
	for (auto component : m_componnets) {
		component->Initialize();
	}
}

void Rain::ECS::SystemBase::Update() {
	for (auto component : m_componnets) {
		component->Update();
	}
}

void Rain::ECS::SystemBase::Destroy() {

}

void Rain::ECS::SystemBase::AddComponent(ComponentBase* component) {
	m_componnets.push_back(component);
}
void Rain::ECS::SystemBase::RemoveComponent(ComponentBase* component) {
	
}
Rain::ECS::ComponentBase* Rain::ECS::SystemBase::GetComponent(int i_id) {
	for (auto component : m_componnets) {
		if (component->id == i_id) {
			return component;
		}
	}
	return nullptr;
}