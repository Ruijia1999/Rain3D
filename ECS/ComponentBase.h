#ifndef RAIN_ECS_COMPONENTBASE
#define RAIN_ECS_COMPONENTBASE
namespace Rain {
	namespace ECS {
		class ComponentBase
		{
			
		public:
			int id;
			ComponentBase();
			ComponentBase(int i_id);
			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Destroy() = 0;
		};
	}
}
#endif


