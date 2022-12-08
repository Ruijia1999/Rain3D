#include "World.h"
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"

void Rain::ECS::World::Initialize() {
	GameObject::GameObjectSystem::GetInstance()->Initialize();
	Transform::TransformSystem::GetInstance()->Initialize();
}
void Rain::ECS::World::Update() {
	GameObject::GameObjectSystem::GetInstance()->Update();
	Transform::TransformSystem::GetInstance()->Update();
	SubmitRenderData();
}

void SubmitRenderData() {

}