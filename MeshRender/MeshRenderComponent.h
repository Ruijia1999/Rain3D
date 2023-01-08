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
			void Update(uint64_t i_timeSinceLastFrame);
			void Destroy();

			const Render::Effect* effect;
			const Render::Mesh* mesh;
			Math::Vector4 color;
			MeshRenderComponent();
			MeshRenderComponent(int i_id,  const Render::Mesh* i_mesh, const Render::Effect* i_effect);
		};

	}
}

#endif //RAIN_TRNASFORM_MeshRenderCOMPONENT