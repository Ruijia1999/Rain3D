#ifndef RAIN_GAMEOBJECT_GAMEOBJECTSYSTEM
#define RAIN_GAMEOBJECT_GAMEOBJECTSYSTEM

#include "ECS/SystemBase.h"
#include "GameObjectComponent.h"
namespace Rain{
	namespace GameObject {
		class GameObjectSystem: public ECS::SystemBase
		{
		public:
			static GameObjectSystem* GetInstance();

		private:
			static GameObjectSystem* instance;
			GameObjectSystem();
		};
	}
}


#endif // !RAIN_GAMEOBJECT_GAMEOBJECTSYSTEM


