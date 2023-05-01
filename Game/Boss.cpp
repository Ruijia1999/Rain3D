#include "Boss.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderComponent.h"
#include "MeshRender/MeshRender.h"
#include "Animation\AnimationSystem.h"

void Rain::Boss::Initialize() {

    Rain::Input::KeyBoard::BindEvent(0x20, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);
        if (animation != nullptr) {
            animation->Play();
        }
        });
    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    collider->OnColliderEnter = [this](const ColliderComponent* other) {
        if (other->entity->tag == "Player") {
            MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->color = Math::Vector4(255 / 255.0f, 0 / 255.0f, 255 / 255.0f, 255 / 255.0f);
        }
       
    };
    collider->OnColliderExit = [this](const ColliderComponent* other) {
        if (other->entity->tag == "Player") {
            MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->color = Math::Vector4(255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 255 / 255.0f);
        }
    };

}
void Rain::Boss::Update(double i_timeSinceLastFrame) {
    Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
    Math::Quaternion i = transform->rotation;
}
Rain::Boss::Boss() :Entity() {

}
Rain::Boss::Boss(int i_id, std::string i_tag, std::string i_name) : Entity(i_id, i_tag, i_name) {

}