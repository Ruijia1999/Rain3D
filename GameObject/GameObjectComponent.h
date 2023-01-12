#ifndef RAIN_GAMEOBJECT_GAMEOBJECTCOMPONENT
#define RAIN_GAMEOBJECT_GAMEOBJECTCOMPONENT
#include "ECS/ComponentBase.h"
#include <vector>
namespace Rain {
	namespace GameObject {
		class GameObjectComponent : public ECS::ComponentBase
		{
		public:
			GameObjectComponent();
			GameObjectComponent(int i_id, bool i_isActive, bool i_isVisible, const char* name, const char* tag);
			GameObjectComponent(int i_id);
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			bool isActive;
			bool isVisible;
			const char* name;
			const char* tag;
			GameObjectComponent* parent;
		private:

			std::vector<GameObjectComponent*> children;

		};
	}
}

#endif // !RAIN_GAMEOBJECT_GAMEOBJECTCOMPONENT






