#ifndef RAIN_MESHRENDER_SYSTEM
#define RAIN_MESHRENDER_SYSTEM
#include "ECS/SystemBase.h"
namespace Rain {
	namespace MeshRender {
		class MeshRenderSystem: public ECS::SystemBase{
		public:
			static MeshRenderSystem* GetInstance();
		private:
			static MeshRenderSystem* instance;
			MeshRenderSystem();
		};
	}
}
#endif // !RAIN_MESHRENDER_SYSTEm
