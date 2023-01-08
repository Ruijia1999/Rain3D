#ifndef RAIN_COLLIDERSYSTEM
#define RAIN_COLLIDERSYSTEM
#include "ECS\SystemBase.h"
#include "Collision.h"
#include "ColliderComponent.h"
namespace Rain {

	class ColliderSystem: public ECS::SystemBase
	{
	public:
		static ColliderSystem* GetInstance();
		void Update(uint64_t i_timeSinceLastFrame);
		bool CheckCollision(const ColliderComponent* i_collider0, const ColliderComponent* i_collider1, const uint64_t i_timeSinceLastFrame);

	private:
		static ColliderSystem* instance;
		ColliderSystem();
		
	};
}


#endif // !RAIN_COLLIDERSYSTEM

