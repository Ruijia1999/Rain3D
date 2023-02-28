#include "Cube.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderComponent.h"
#include "MeshRender/MeshRender.h"
#include "Animation\AnimationSystem.h"
void Rain::Cube::Initialize() {

    Rain::Input::KeyBoard::BindEvent(0x20, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);
        animation->Play();
        /* Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
            transform->position = transform->position + Math::Vector3(0.3f, 0, 0);*/
        });
    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);

  
}
void Rain::Cube::Update(double i_timeSinceLastFrame) {

}
Rain::Cube::Cube() :Entity() {

}
Rain::Cube::Cube(int i_id, std::string i_tag, std::string i_name):Entity(i_id, i_tag, i_name) {

}