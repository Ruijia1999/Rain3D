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
			Entity() {
				id = -1;
				tag = "";
				name = "";
			}
			Entity(int i_id, std::string i_tag, std::string i_name){
				id = i_id;
				name = i_name;
				tag = i_tag;
			}
			virtual void Initialize();
			virtual void Update(double i_timeSinceLastFrame);
		};

	}
}
#endif // !RAIN_ECS_ENTITY

