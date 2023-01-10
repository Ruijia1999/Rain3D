#include "Circle.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
void Rain::Circle::Initialize(int i_id) {
    id = i_id;

    //Click and the object will move forward.
    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0.0f, 0, 0.49f);
        int o = 1;
        });

    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    collider->OnColliderEnter = [this](const ColliderComponent* other) {
        MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->color = Math::Vector4(220 / 255.0f, 20 / 255.0f, 60/ 255.0f, 255 / 255.0f);
    };
    collider->OnColliderExit = [this](const ColliderComponent* other) {
        MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->color = Math::Vector4(144/255.0f, 238 / 255.0f, 144 / 255.0f, 255 / 255.0f);
    };
    //Press A and the object will move to the left.
    Rain::Input::KeyBoard::BindEvent(0x41, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position - Math::Vector3(0.001f, 0, 0);
        });
    //w
    Rain::Input::KeyBoard::BindEvent(0x57, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0, 0, 0.001f);
        });
    //S
    Rain::Input::KeyBoard::BindEvent(0x53, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position - Math::Vector3(0, 0, 0.001f);
        });
    //D
    Rain::Input::KeyBoard::BindEvent(0x44, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0.001f, 0, 0);
        });
}
void Rain::Circle::Update(double i_timeSinceLastFrame) {
    /*Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
    if(i_timeSinceLastFrame>0)
    transform->position.x -= i_timeSinceLastFrame * 1;*/
}
void Rain::Circle::Destory() {

}
Rain::Circle::Circle() {
}