#include "Circle.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
void Rain::Circle::Initialize(int i_id) {
    id = i_id;
    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0.0f, 0, 0.49f);
        int o = 1;
        });

    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    collider->OnColliderEnter = [this](const ColliderComponent* other) {
        MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->mesh = MeshRender::MeshRenderSystem::GetInstance()->meshes.find("cube.hrj")->second;
    };
    collider->OnColliderExit = [this](const ColliderComponent* other) {
        MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->mesh = MeshRender::MeshRenderSystem::GetInstance()->meshes.find("ss.hrj")->second;
    };
}

Rain::Circle::Circle() {
}