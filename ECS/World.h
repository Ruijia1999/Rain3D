#ifndef RAIN_ECS_WORLD
#define RAIN_ECS_WORLD

namespace Rain {
	namespace ECS {
		class World
		{
		public:
			void Initialize();
			void Update();

		private:
			void SubmitRenderData();
		};
	}
}


#endif
