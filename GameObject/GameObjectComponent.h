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
			GameObjectComponent(int i_id);
			void Initialize();
			void Update(uint64_t i_timeSinceLastFrame);
			void Destroy();

			bool m_isActive;
			bool m_isVisible;
		private:

			std::vector<GameObjectComponent*> m_children;
			GameObjectComponent* m_parent;
		};
	}
}

#endif // !RAIN_GAMEOBJECT_GAMEOBJECTCOMPONENT






