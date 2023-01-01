#include "ColliderComponent.h"
#include "Transform\TransformSystem.h"
#include "Transform\TransformComponent.h"
void Rain::ColliderComponent::Intersect(const Rain::ColliderComponent* i_collider) {
	curIntersections.insert(i_collider);
}
void Rain::ColliderComponent::Initialize() {

}

void Rain::ColliderComponent::Update(uint64_t i_timeSinceLastFrame) {
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	collider->Update(Math::Quaternion(0, 0, 0, 1), transform->position);
	CheckIntersections();
	swap(curIntersections, prvIntersections);
	curIntersections.clear();
}
void Rain::ColliderComponent::Destroy() {

}
Rain::ColliderComponent::ColliderComponent(int i_id, const char* i_type):ComponentBase(i_id) {
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
	if (strcmp(i_type, "AABB") == 0) {
		type = Collision::ColliderType::AABB;
		collider = (Collision::ColliderBase*)new Collision::AABBCollider(Math::Quaternion(0,0,0,1),transform->position);
	}else if (strcmp(i_type, "OBB") == 0) {
		type = Collision::ColliderType::OBB;
		collider = (Collision::ColliderBase*)new Collision::OBBCollider(Math::Quaternion(0, 0, 0, 1), transform->position);
	}
	else if (strcmp(i_type, "Sphere") == 0) {
		type = Collision::ColliderType::Sphere;
		collider = (Collision::ColliderBase*)new Collision::SphereCollider(Math::Quaternion(0, 0, 0, 1), transform->position);
	}
}
void Rain::ColliderComponent::CheckIntersections() {
	for (auto collider : prvIntersections) {
		if (curIntersections.find(collider)!=curIntersections.end()) {
			if(OnColliderStay!=nullptr)
			OnColliderStay(collider);
		}
		else {
			if (OnColliderExit != nullptr)
			OnColliderExit(collider);
		}
	}

	for (auto collider : curIntersections) {
		if (prvIntersections.find(collider) == prvIntersections.end()) {
			if (OnColliderEnter != nullptr)
			OnColliderEnter(collider);
		}
	}

}

