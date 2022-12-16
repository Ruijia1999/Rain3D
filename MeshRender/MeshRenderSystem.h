#ifndef RAIN_MESHRENDER_SYSTEM
#define RAIN_MESHRENDER_SYSTEM
#include "Render/Effect.h"
#include "Render/Mesh.h"
#include "ECS/SystemBase.h"
#include <map>
namespace Rain {
	namespace MeshRender {
		class MeshRenderSystem: public ECS::SystemBase{
		public:
			static MeshRenderSystem* GetInstance();

			void Initialize();
			std::map<std::string, Render::Effect*> effects;
			std::map<std::string, Render::Mesh*> meshes;

		private:
			static MeshRenderSystem* instance;
			MeshRenderSystem();
		};
	}
}
#endif // !RAIN_MESHRENDER_SYSTEm
