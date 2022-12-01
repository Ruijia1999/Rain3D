#include "TransformComponent.h"
Rain::Transform::TransformComponent::TransformComponent() {
	m_Position = Math::Vector3();
	m_Scale = Math::Vector3(1, 1, 1);
	m_Rotation = Math::Vector3();
}