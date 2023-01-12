#ifndef RAIN_TRNASFORM_MeshRenderCOMPONENT
#define RAIN_TRNASFORM_MeshRenderCOMPONENT

#include "Math/Math.h"
#include "Render/Effect.h"
#include "Render/Mesh.h"
#include "ECS/ComponentBase.h"
#include <vector>
#include "Math/Vector4.h"
namespace Rain {
	namespace MeshRender {
		class MeshRenderComponent : public ECS::ComponentBase
		{
		public:
			void Initialize();
			void Update(double i_timeSinceLastFrame);
			void Destroy();

			const Render::Effect* effect;
			const Render::Mesh* mesh;
			Math::Vector4 color;
			MeshRenderComponent();
			MeshRenderComponent(int i_id,  const Render::Mesh* i_mesh, const Render::Effect* i_effect, Math::Vector4 i_color = Math::Vector4(1, 1, 1, 1));
		};

	}
}

#endif //RAIN_TRNASFORM_MeshRenderCOMPONENT