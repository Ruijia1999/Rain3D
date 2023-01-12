#include "Enemy.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
void Rain::Enemy::Initialize(int i_id, std::string i_tag, std::string i_name) {
    id = i_id;
    name = i_name;
    tag = i_tag;
}
void Rain::Enemy::Update(double i_timeSinceLastFrame) {

}
Rain::Enemy::Enemy() {
}