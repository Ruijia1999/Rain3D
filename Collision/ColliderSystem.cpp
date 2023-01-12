#include "ColliderSystem.h"
Rain::ColliderSystem* Rain::ColliderSystem::instance;

Rain::ColliderSystem* Rain::ColliderSystem::GetInstance() {
	if (instance == nullptr) {
		instance = new ColliderSystem();
		return instance;
	}
	else {
		return instance;
	}
}

Rain::ColliderSystem::ColliderSystem() {

}
#ifdef OCTREE

void Rain::Collision::Update(const float i_timeSinceLastFrame) {
	cResult result = Results::Success;
	s_Octree = new Octree();
	for (int i = 0; i < 1024; i++) {
		if (s_Colliders[i] != nullptr && s_Colliders[i]->isActive) {
			s_Colliders[i]->CheckColliders(i_timeSinceLastFrame);
			if (s_Colliders[i]->type != ColliderType::AABB) {
				EAE6320_ASSERTF(false, "Failed to use Octree optimization. Only AABB Collider can be optimized.");
				Logging::OutputError("Failed to use Octree optimization. Only AABB Collider can be optimized.");
				return Results::Failure;
			}
			s_Octree->Insert(s_Colliders[i]);
		}
	}

	//Octree traversal
	s_Octree->Check();

	return result;
}

#else

void Rain::ColliderSystem::Update(double i_timeSinceLastFrame) {

	for (auto component1 : m_componnets) {
		for (auto component2 : m_componnets) {
			if (component1 != component2) {
				if (CheckCollision((ColliderComponent*)component1, (ColliderComponent*)component2, i_timeSinceLastFrame)) {
					((ColliderComponent*)component1)->Intersect((ColliderComponent*)component2);
				}
			}

		}
	}

	for (auto component : m_componnets) {
		component->Update(i_timeSinceLastFrame);
	}

}
#endif // OCTREE


bool Rain::ColliderSystem::CheckCollision(const ColliderComponent* i_collider0, const ColliderComponent* i_collider1, const double i_timeSinceLastFrame) {
	
	switch (i_collider0->type)
	{
	case Collision::ColliderType::Sphere:
		switch (i_collider1->type)
		{
		case Collision::ColliderType::Sphere:
			return Collision::SphereSphere((Collision::SphereCollider*)i_collider0->collider, (Collision::SphereCollider*)i_collider1->collider, i_timeSinceLastFrame);
			break;
		case Collision::ColliderType::AABB:
			return Collision::BoxSphere((Collision::AABBCollider*)i_collider1->collider, (Collision::SphereCollider*)i_collider0->collider, i_timeSinceLastFrame);
			break;
		case Collision::ColliderType::OBB:
			return Collision::BoxSphereOBB((Collision::OBBCollider*)i_collider1->collider, (Collision::SphereCollider*)i_collider0->collider, i_timeSinceLastFrame);
			break;
		}
		break;
	case Collision::ColliderType::AABB:
		switch (i_collider1->type)
		{
		case Collision::ColliderType::Sphere:
			return Collision::BoxSphere((Collision::AABBCollider*)i_collider0->collider, (Collision::SphereCollider*)i_collider1->collider, i_timeSinceLastFrame);
			break;
		case Collision::ColliderType::AABB:
			return Collision::BoxBox((Collision::AABBCollider*)i_collider0->collider, (Collision::AABBCollider*)i_collider1->collider, i_timeSinceLastFrame);
			break;
		case Collision::ColliderType::OBB:
			return Collision::BoxBoxOBB((Collision::AABBCollider*)i_collider0->collider, (Collision::OBBCollider*)i_collider1->collider, i_timeSinceLastFrame);
			break;
		}
		break;
	case Collision::ColliderType::OBB:
		switch (i_collider1->type)
		{
		case Collision::ColliderType::Sphere:
			return Collision::BoxSphereOBB((Collision::OBBCollider*)i_collider0->collider, (Collision::SphereCollider*)i_collider1->collider, i_timeSinceLastFrame);
			break;
		case Collision::ColliderType::OBB:
			return Collision::BoxOBBBoxOBB((Collision::OBBCollider*)i_collider0->collider, (Collision::OBBCollider*)i_collider1->collider, i_timeSinceLastFrame);
			break;
		case Collision::ColliderType::AABB:
			return Collision::BoxBoxOBB((Collision::AABBCollider*)i_collider1->collider, (Collision::OBBCollider*)i_collider0->collider, i_timeSinceLastFrame);
			break;
		}
		break;
	}


	return false;
}
