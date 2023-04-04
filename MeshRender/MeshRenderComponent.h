#ifndef RAIN_TRNASFORM_MeshRenderCOMPONENT
#define RAIN_TRNASFORM_MeshRenderCOMPONENT

#include "Math/Math.h"
#include "Render/Effect.h"
#include "Render/Mesh.h"
#include "Render/SkeletalMesh.h"
#include "Render/Texture.h"
#include "ECS/ComponentBase.h"
#include <vector>
#include <memory>
#include "Math/Vector4.h"
namespace Rain {
	namespace MeshRender {
		class MeshRenderComponent : public ECS::ComponentBase
		{
		public:
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			int meshType;
			std::shared_ptr <Render::Effect> effect;
			std::shared_ptr < Render::Mesh> mesh;
			std::shared_ptr <Render::SkeletalMesh> skeletalMesh;
			std::shared_ptr < Render::Texture> texture ;
			std::shared_ptr < Render::Texture> normalMap;
			Math::Vector4 color;
			MeshRenderComponent();
			MeshRenderComponent(int i_id,  const std::shared_ptr <Render::Mesh>& i_mesh, const std::shared_ptr < Render::Effect>& i_effect, Math::Vector4 i_color = Math::Vector4(1, 1, 1, 1));
			MeshRenderComponent(int i_id, const std::shared_ptr <Render::Mesh>& i_mesh, const std::shared_ptr < Render::Effect>& i_effect, std::shared_ptr<Render::Texture> i_texture, std::shared_ptr<Render::Texture> i_normalMap, Math::Vector4 i_color = Math::Vector4(1, 1, 1, 1));
			MeshRenderComponent(int i_id, const std::shared_ptr <Render::SkeletalMesh>& i_mesh, const std::shared_ptr < Render::Effect>& i_effect, Math::Vector4 i_color = Math::Vector4(1, 1, 1, 1));
			~MeshRenderComponent() {
				int j = 0;
			}

			MeshRenderComponent& operator=(const MeshRenderComponent& i) {
				int j = 0;
			}
			MeshRenderComponent(const MeshRenderComponent& i) {
				int j = 0;
			}
		};

	}
}

#endif //RAIN_TRNASFORM_MeshRenderCOMPONENT