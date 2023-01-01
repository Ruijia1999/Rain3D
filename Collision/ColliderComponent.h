#ifndef RAIN_COLLIDERCOMPONENT
#define RAIN_COLLIDERCOMPONENT
#include "ECS\ComponentBase.h"
#include "Math\Vector3.h"
#include "Math\Quaternion.h"
#include "Collision.h"
#include "ColliderBase.h"
#include <functional>
#include <unordered_set>
namespace Rain {
	class ColliderComponent : public ECS::ComponentBase
	{
	public:
		Collision::ColliderType type;
		Collision::ColliderBase* collider;


		void Update(uint64_t i_timeSinceLastFrame);
		std::function<void(const ColliderComponent*)> OnColliderEnter;
		std::function<void(const ColliderComponent*)> OnColliderStay;
		std::function<void(const ColliderComponent*)> OnColliderExit;
		void Intersect(const ColliderComponent* i_collider);


	private:
		//The colliders that were intersected with this collider in the last frame
		std::unordered_set<const ColliderComponent*> prvIntersections;
		//The colliders that were intersected with this collider in this frame
		std::unordered_set<const ColliderComponent*> curIntersections;
		void CheckIntersections();
	};
}


#endif // !RAIN_COLLIDERSYSTEM


