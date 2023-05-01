#ifndef BOSS
#define BOSS
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"

namespace Rain {
	class Boss : public ECS::Entity
	{
	public:
		ENTITY(Boss)
			Boss();
		Boss(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void Update(double i_timeSinceLastFrame);

	};
	REGIST(Boss)

}

#endif

