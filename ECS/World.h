#ifndef RAIN_ECS_WORLD
#define RAIN_ECS_WORLD

namespace Rain {
	namespace ECS {
		class World
		{
		public:
			static World* GetInstance();
			void Initialize();
			void Update();

		private:
			static World* Instance;
			void SubmitRenderData();
			void InitializeGameScene();
		};
	}
}


#endif
