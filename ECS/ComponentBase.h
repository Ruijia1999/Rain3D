#ifndef RAIN_ECS_COMPONENTBASE
#define RAIN_ECS_COMPONENTBASE
#include <cstdint>
#include <memory>
#include "Entity.h"
namespace Rain {
	namespace ECS {
		class ComponentBase
		{
		public:
			int id;
			std::shared_ptr <Entity> entity;
			ComponentBase();
			ComponentBase(int i_id, std::shared_ptr <Entity> i_entity);
			virtual void Initialize() = 0;
			virtual void Update(double i_timeSinceLastFrame) = 0;
			virtual void Destroy() = 0;
		};
	}
}
#endif


