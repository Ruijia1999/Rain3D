#include "ColliderComponent.h"

void Rain::ColliderComponent::Intersect(const Rain::ColliderComponent* i_collider) {
	curIntersections.insert(i_collider);
}

void Rain::ColliderComponent::Update(uint64_t i_timeSinceLastFrame) {
	CheckIntersections();
	swap(curIntersections, prvIntersections);
	curIntersections.clear();
}
void Rain::ColliderComponent::CheckIntersections() {
	for (auto collider : prvIntersections) {
		if (curIntersections.find(collider)!=curIntersections.end()) {
			OnColliderStay(collider);
		}
		else {
			OnColliderExit(collider);
		}
	}

	for (auto collider : curIntersections) {
		if (prvIntersections.find(collider) == curIntersections.end()) {
			OnColliderEnter(collider);
		}
	}

}

