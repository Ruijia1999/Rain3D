#include "Enemy.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
void Rain::Enemy::Initialize(int i_id) {
    id = i_id;
}
void Rain::Enemy::Update(double i_timeSinceLastFrame) {

}
Rain::Enemy::Enemy() {
}