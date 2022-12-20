#ifndef CIRCLE
#define CIRCLE
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"

namespace Rain {
	class Circle : public ECS::Entity
	{
	public:
		ENTITY(Circle)
		Circle();
		void Initialize(int i_id);

	};
	REGIST(Circle)
}

#endif
