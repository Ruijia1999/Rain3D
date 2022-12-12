#ifndef RAIN_TRANSFORM_TRANSFORMSYSTEM
#define RAIN_TRANSFORM_TRANSFORMSYSTEM

#include "ECS/SystemBase.h"
#include "TransformComponent.h"

namespace Rain {
	namespace Transform {
		class TransformSystem: public ECS::SystemBase
		{
		public:
			static TransformSystem* GetInstance();
		private:
			static TransformSystem* instance;
			TransformSystem();
		};
	}
}


#endif // !RAIN_TRANSFORM_TRANSFORMSYSTEM


