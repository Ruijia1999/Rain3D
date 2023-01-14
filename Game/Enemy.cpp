#include "Enemy.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
Rain::Enemy::Enemy() :Entity() {

}

Rain::Enemy::Enemy(int i_id, std::string i_tag, std::string i_name):Entity(i_id, i_tag, i_name) {
}