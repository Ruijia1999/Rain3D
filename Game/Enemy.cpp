#include "Enemy.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
#include "Animation\AnimationSystem.h"
#include "EngineLog\EngineLog.h"
#include "Animation\SklAnimationComponent.h"
void Rain::Enemy::Initialize() {
    isAttacked = false;
    speed = 5;
#pragma region Movement
    //A
    Rain::Input::KeyBoard::BindEvent(0x41, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        
        StartRun();
  
        });


    Rain::Input::KeyBoard::BindEvent(0x41, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
 
        if (!isAttacked) {
            StartRun();
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
            
            Math::Vector4 newPos = Math::Matrix(Math::Quaternion(transform->rotation.x, -transform->rotation.y, transform->rotation.z, transform->rotation.w)) * Math::Vector4(-1,0,0,1);
            Math::Vector3 direction(newPos.x,newPos.y, newPos.z);
            direction.Normalize();
            transform->position = transform->position + direction*speed;
        }
        });

    Rain::Input::KeyBoard::BindEvent(0x41, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        if (!isAttacked) {
            Stand();
          
        }

        });

    //D
    Rain::Input::KeyBoard::BindEvent(0x44, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {

        StartRun();
     
        });


    Rain::Input::KeyBoard::BindEvent(0x44, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {

        if (!isAttacked) {
            StartRun();
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
            Math::Vector4 newPos = Math::Matrix(Math::Quaternion(transform->rotation.x, -transform->rotation.y, transform->rotation.z, transform->rotation.w)) * Math::Vector4(1, 0, 0, 1);
            Math::Vector3 direction(newPos.x, newPos.y, newPos.z);
            direction.Normalize();
            transform->position = transform->position + direction * speed;
        }
        });

    Rain::Input::KeyBoard::BindEvent(0x44, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        if (!isAttacked) {
            Stand();
        }

        });

    //W
    Rain::Input::KeyBoard::BindEvent(0x57, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        StartRun();

        });


    Rain::Input::KeyBoard::BindEvent(0x57, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        if (!isAttacked) {
            StartRun();
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
            Math::Vector4 newPos = Math::Matrix(Math::Quaternion(transform->rotation.x, -transform->rotation.y, transform->rotation.z, transform->rotation.w)) * Math::Vector4(0, 0,1, 1);
            Math::Vector3 direction(newPos.x, newPos.y, newPos.z);
            direction.Normalize();
            transform->position = transform->position + direction * speed;
        }
        });

    Rain::Input::KeyBoard::BindEvent(0x57, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        if (!isAttacked) {
            Stand();
        }

        });

    //S
    Rain::Input::KeyBoard::BindEvent(0x53, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        StartRun();

        });


    Rain::Input::KeyBoard::BindEvent(0x53, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {

        if (!isAttacked) {
            StartRun();
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
            Math::Vector4 newPos = Math::Matrix(Math::Quaternion(transform->rotation.x, -transform->rotation.y, transform->rotation.z, transform->rotation.w)) * Math::Vector4(0, 0, -1, 1);
            Math::Vector3 direction(newPos.x, newPos.y, newPos.z);
            direction.Normalize();
            transform->position = transform->position + direction * speed;
 }
        });

    Rain::Input::KeyBoard::BindEvent(0x53, KEYUP, [this](Rain::Input::KeyBoard::KeyInfo info) {
        if (!isAttacked) {
            Stand();
       }
  

        });
#pragma endregion

#pragma region Combat
    //A
    /*Rain::Input::KeyBoard::BindEvent(0x42, KEYDOWN, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Attacked();
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->rotation = Math::Quaternion(0, 1, 0, 0);
        });*/

    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    if (collider != nullptr) {
        collider->OnColliderEnter = [this](const ColliderComponent* other) {
            Attacked();
        };
    }

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
    isAttacked = true;
    if (animation != nullptr) {
        if (((Animation::SklAnimationComponent*)animation)->currentClip->name != "Attacked") {
            ((Animation::SklAnimationComponent*)animation)->SetClip("Attacked");
        }
    }
}