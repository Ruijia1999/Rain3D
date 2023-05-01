#include "PlayerCamera.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderComponent.h"
#include "MeshRender/MeshRender.h"
#include "Animation\AnimationSystem.h"
#include "EngineLog\EngineLog.h"
#include "GameObject\GameObjectSystem.h"

void Rain::PlayerCamera::Initialize() {
    camera = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
    int playerID = GameObject::GameObjectSystem::GetInstance()->GetIDByName("player");
    player = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(0);
    orgCameraPos = camera->position;
    orgDiversity =orgCameraPos- player->position ;
    mouseSensitivity = 100000;
    orgMouseCoord = Input::Mouse::mousePosition;

}
void Rain::PlayerCamera::Update(double i_timeSinceLastFrame) {
    Math::Vector2 mousePos = Input::Mouse::mousePosition;
    float hor = (mousePos.x-800)/ mouseSensitivity;
    
    camera->rotation = Math::Quaternion(0, -hor * 90, 0);
    player->rotation = Math::Quaternion(0, hor * 90, 0);
  
    Math::Vector4 pos(orgDiversity.x, 0, orgDiversity.z,1);
    Math::Vector4 newPos = Math::Matrix(Math::Quaternion(0, -hor * 90, 0)) * pos;

    camera->position.x = player->position.x + newPos.x;
    camera->position.z = player->position.z + newPos.z;
    camera->position.y = orgCameraPos.y;
}
Rain::PlayerCamera::PlayerCamera() :Entity() {

}
Rain::PlayerCamera::PlayerCamera(int i_id, std::string i_tag, std::string i_name) : Entity(i_id, i_tag, i_name) {

}