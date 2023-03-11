#include "Enemy.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
#include "Animation\AnimationSystem.h"
void Rain::Enemy::Initialize() {
    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);
        if (animation != nullptr) {
            if (animation->isPlaying) {
                animation->Stop();
            }
            else {
                animation->Play();
            }
        }
        
        });

    Rain::Input::Mouse::BindEvent(MOUSE_RIGHT_DOWN, [this](Rain::Input::MouseInfo info) {
        Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);
        if (animation->isPlaying) {
            animation->Pause();
        }else {
            animation->Play();
        }

        });
    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
}

Rain::Enemy::Enemy(int i_id, std::string i_tag, std::string i_name):Entity(i_id, i_tag, i_name) {
}
Rain::Enemy::Enemy() : Entity() {
}

void Rain::Enemy::Update(double i_timeSinceLastFrame) {

}