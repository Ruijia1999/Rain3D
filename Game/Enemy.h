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
		Enemy(int i_id, std::string i_tag, std::string i_name);

	};
	REGIST(Enemy)
}

#endif
