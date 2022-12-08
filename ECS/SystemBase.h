#ifndef RAIN_ECS_SYSTEMBASE
#define RAIN_ECS_SYSTEMBASE

#include <vector>
#include "ComponentBase.h"
namespace Rain {
	namespace ECS {
		
		class SystemBase
		{
			
		public:

			static SystemBase* GetInstance();
			
			void Initialize();
			void Update();
			void Destroy();

			void AddComponent(ComponentBase* component);
			void RemoveComponent(ComponentBase* component);
			ComponentBase* GetComponent(int i_id);

		private:
			std::vector<ComponentBase*> m_componnets;

			SystemBase();
			static SystemBase* Instance;
		};
	}
}

#endif // !RAIN_ECS_SYSTEMBASE