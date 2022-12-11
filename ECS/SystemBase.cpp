#include "SystemBase.h"

Rain::ECS::SystemBase* Rain::ECS::SystemBase::Instance;
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

void Rain::ECS::SystemBase::Update(uint64_t i_timeSinceLastFrame) {
	for (auto component : m_componnets) {
		component->Update(i_timeSinceLastFrame);
	}
}

void Rain::ECS::SystemBase::Destroy() {

}

void Rain::ECS::SystemBase::AddComponent(ComponentBase* component) {
	m_componnets.push_back(component);
}

void Rain::ECS::SystemBase::RemoveComponent(const int i_id) {
//TODO
}

template<class T>
T* Rain::ECS::SystemBase::GetComponent(const int i_id) {
	for (auto component : m_componnets) {
		if (component->id == i_id) {
			return component;
		}
	}
	return nullptr;
}