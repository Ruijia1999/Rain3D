#include "Circle.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
void Rain::Circle::Initialize(int i_id) {
    id = i_id;
    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position - Math::Vector3(0.1f, 0, 0);
        int o = 1;
        });
}

Rain::Circle::Circle() {
}