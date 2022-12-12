#include "TransformComponent.h"
Rain::Transform::TransformComponent::TransformComponent() {
	m_Position = Math::Vector3();
	m_Scale = Math::Vector3(1, 1, 1);
	m_Rotation = Math::Vector3();
}
Rain::Transform::TransformComponent::TransformComponent(Math::Vector3 i_Position, Math::Vector3 i_Scale, Math::Vector3 i_Rotation){
	m_Position = i_Position;
	m_Scale = i_Scale;
	m_Rotation = i_Rotation;
}
void Rain::Transform::TransformComponent::Initialize() {

}
void Rain::Transform::TransformComponent::Update(uint64_t i_timeSinceLastFrame) {

}
void Rain::Transform::TransformComponent::Destroy() {

}