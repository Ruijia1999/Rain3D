#ifndef RAIN_ECS_SYSTEMBASE
#define RAIN_ECS_SYSTEMBASE

#include <vector>
#include <iostream>
#include "ComponentBase.h"
namespace Rain {
	namespace ECS {
		
		class SystemBase
		{
			
		public:

			static SystemBase* GetInstance();
			
			void Initialize();
			void Update(uint64_t i_timeSinceLastFrame);
			void Destroy();

			void AddComponent(ComponentBase* component);
			void RemoveComponent(const int i_id);

			template<class T>
			T* GetComponent(const int i_id);

		private:
			std::vector<ComponentBase*> m_componnets;

			SystemBase();
			static SystemBase* Instance;
		};
	}
}

#endif // !RAIN_ECS_SYSTEMBASE