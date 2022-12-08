#ifndef RAIN_RENDER_RENDERSYSTEM
#define RAIN_RENDER_RENDERSYSTEM


#include <Windows.h>
#include "Mesh.h"
#include "Effect.h"
#include "ECS/ComponentBase.h"
namespace Rain {
	namespace Render {
		class RenderComponent: ECS::ComponentBase
		{
		public:
			Mesh* s_mesh = nullptr;
			Effect* s_effect = nullptr;
		};
	}
}

#endif //RAIN_RENDERSYSTEM