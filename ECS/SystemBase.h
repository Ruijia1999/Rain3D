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


			
			void Initialize();
			void Update(uint64_t i_timeSinceLastFrame);
			void Destroy();

			void AddComponent(ComponentBase* component);
			void RemoveComponent(const int i_id);

			template<class T>
			T* GetComponent(const int i_id) {
				for (auto component : m_componnets) {
					if (component->id == i_id) {
						return (T*)component;
					}
				}
				return nullptr;
			}
			template<class T>
			std::vector<T*> GetAllComponents() {
				std::vector<T*> results;
				for (auto component : m_componnets) {
					results.push_back((T*)component);
				}
				return results;
			}
			SystemBase();
		private:
			std::vector<ComponentBase*> m_componnets;

	

		};
	}
}

#endif // !RAIN_ECS_SYSTEMBASE