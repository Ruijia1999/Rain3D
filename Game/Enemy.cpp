#include "Enemy.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
#include "Animation\AnimationSystem.h"
#include "Animation\SklAnimationComponent.h"
void Rain::Enemy::Initialize() {
#pragma region Movement
    //A
    Rain::Input::KeyBoard::BindEvent(0x41, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        StartRun();
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->rotation = Math::Quaternion(0, -0.7071068, 0, 0.7071068);
        });


    Rain::Input::KeyBoard::BindEvent(0x41, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(-2, 0, 0);
        StartRun();
        });

    Rain::Input::KeyBoard::BindEvent(0x41, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Stand();

        });

    //D
    Rain::Input::KeyBoard::BindEvent(0x44, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        StartRun();
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->rotation = Math::Quaternion(0, 0.7071068, 0, 0.7071068);
        });


    Rain::Input::KeyBoard::BindEvent(0x44, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(2, 0, 0);
        StartRun();
        });

    Rain::Input::KeyBoard::BindEvent(0x44, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Stand();

        });

    //W
    Rain::Input::KeyBoard::BindEvent(0x57, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        StartRun();
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->rotation = Math::Quaternion(0, 0, 0, 1);
        });


    Rain::Input::KeyBoard::BindEvent(0x57, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0, 0, 2);
        StartRun();
        });

    Rain::Input::KeyBoard::BindEvent(0x57, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Stand();

        });

    //S
    Rain::Input::KeyBoard::BindEvent(0x53, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        StartRun();
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->rotation = Math::Quaternion(0, 1, 0, 0);
        });


    Rain::Input::KeyBoard::BindEvent(0x53, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0, 0, -2);
        StartRun();
        });

    Rain::Input::KeyBoard::BindEvent(0x53, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Stand();

        });
#pragma endregion

#pragma region Combat
    //A
    Rain::Input::KeyBoard::BindEvent(0x42, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Attacked();
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->rotation = Math::Quaternion(0, 1, 0, 0);
        });

   /* ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    if (collider != nullptr) {
        collider->OnColliderEnter = [this](const ColliderComponent* other) {
            Attacked();
        };
    }*/

#pragma endregion

  

}

Rain::Enemy::Enemy(int i_id, std::string i_tag, std::string i_name):Entity(i_id, i_tag, i_name) {
}
Rain::Enemy::Enemy() : Entity() {
}

void Rain::Enemy::Update(double i_timeSinceLastFrame) {
 
}

void Rain::Enemy::StartRun() {
    Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);

    if (animation != nullptr) {
        if (((Animation::SklAnimationComponent*)animation)->currentClip->name != "Run") {
            ((Animation::SklAnimationComponent*)animation)->SetClip("Run");
        }
    }
}
void Rain::Enemy::Stand() {
    Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);

    if (animation != nullptr) {
        if (((Animation::SklAnimationComponent*)animation)->currentClip->name != "Idle") {
            ((Animation::SklAnimationComponent*)animation)->SetClip("Idle");
        }
    }
}
void Rain::Enemy::Attacked() {
    Animation::AnimationComponent* animation = Animation::AnimationSystem::GetInstance()->GetComponent<Animation::AnimationComponent>(this->id);

    if (animation != nullptr) {
        if (((Animation::SklAnimationComponent*)animation)->currentClip->name != "Attacked") {
            ((Animation::SklAnimationComponent*)animation)->SetClip("Attacked");
        }
    }
}