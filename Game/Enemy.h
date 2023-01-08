#ifndef ENEMY
#define ENEMY
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"

namespace Rain {
	class Enemy : public ECS::Entity
	{
	public:
		ENTITY(Enemy)
			Enemy();
		void Initialize(int i_id);
		void Update(double i_timeSinceLastFrame);

	};
	REGIST(Enemy)
}

#endif
