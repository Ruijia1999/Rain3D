#ifndef RAIN_ECS_ENTITY
#define RAIN_ECS_ENTITY
#include <string>
namespace Rain {
	namespace ECS {
		class Entity
		{
		public:
			int id;
			std::string tag;
			std::string name;
			virtual void Initialize(int id, std::string i_tag, std::string i_name ) = 0;
			virtual void Update(double i_timeSinceLastFrame) = 0;
		};

	}
}
#endif // !RAIN_ECS_ENTITY

