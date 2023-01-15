#ifndef RAIN_MESHRENDER_SYSTEM
#define RAIN_MESHRENDER_SYSTEM
#include "Render/Effect.h"
#include "Render/Mesh.h"
#include "ECS/SystemBase.h"
#include "MeshRenderComponent.h"
#include <map>
namespace Rain {
	namespace MeshRender {
		class MeshRenderSystem: public ECS::SystemBase{
		public:
			static MeshRenderSystem* GetInstance();

			void Initialize();
			void ClearUp () {
				Destroy<MeshRenderComponent>();
				delete instance;
			}
			std::map<std::string, std::shared_ptr<Render::Effect>> effects;
			std::map<std::string, std::shared_ptr<Render::Mesh>> meshes;
			std::shared_ptr<Render::Mesh> InitializeMesh(const char* i_name);
		private:
			static MeshRenderSystem* instance;
			MeshRenderSystem();
			~MeshRenderSystem() {
				int i = 0;
			}
		};
	}
}
#endif // !RAIN_MESHRENDER_SYSTEm
