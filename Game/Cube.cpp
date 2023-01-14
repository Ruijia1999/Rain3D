#include "Cube.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderComponent.h"
#include "MeshRender/MeshRender.h"
void Rain::Cube::Initialize() {

    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        //transform->position = transform->position + Math::Vector3(0.3f, 0, 0);
        });
    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);

  
}
void Rain::Cube::Update(double i_timeSinceLastFrame) {

}
Rain::Cube::Cube() :Entity() {

}
Rain::Cube::Cube(int i_id, std::string i_tag, std::string i_name):Entity(i_id, i_tag, i_name) {

}