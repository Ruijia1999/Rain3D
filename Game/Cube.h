#ifndef CUBE
#define CUBE
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"

namespace Rain {
	class Cube : public ECS::Entity
	{
	public:
		ENTITY(Cube)
		Cube();
		Cube(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void Update(double i_timeSinceLastFrame);

	};
	REGIST(Cube)
}

#endif

