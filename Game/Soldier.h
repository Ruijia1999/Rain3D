#ifndef SOLDIER
#define SOLDIER
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"

namespace Rain {
	class Soldier : public ECS::Entity
	{
	public:
		ENTITY(Soldier)
		Soldier();
		Soldier(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void Update(double i_timeSinceLastFrame);

	};
	REGIST(Soldier)
}

#endif
