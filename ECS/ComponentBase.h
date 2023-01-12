#ifndef RAIN_ECS_COMPONENTBASE
#define RAIN_ECS_COMPONENTBASE
#include <cstdint>
namespace Rain {
	namespace ECS {
		class ComponentBase
		{
		public:
			int id;
			bool active;

			ComponentBase();
			ComponentBase(int i_id);
			virtual void Initialize() = 0;
			virtual void Update(double i_timeSinceLastFrame) = 0;
			virtual void Destroy() = 0;
		};
	}
}
#endif


