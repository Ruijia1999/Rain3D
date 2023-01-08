#include "TransformComponent.h"
Rain::Transform::TransformComponent::TransformComponent() {
	position = Math::Vector3();
	scale = Math::Vector3(1, 1, 1);
	rotation = Math::Quaternion();
}
Rain::Transform::TransformComponent::TransformComponent(int i_id, Math::Vector3 i_Position, Math::Vector3 i_Scale, Math::Quaternion i_Rotation){
	id = i_id;
	position = i_Position;
	scale = i_Scale;
	rotation = i_Rotation;
}
void Rain::Transform::TransformComponent::Initialize() {

}
void Rain::Transform::TransformComponent::Update(uint64_t i_timeSinceLastFrame) {

}
void Rain::Transform::TransformComponent::Destroy() {

}