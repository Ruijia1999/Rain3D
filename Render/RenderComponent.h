#ifndef RAIN_RENDER_RENDERSYSTEM
#define RAIN_RENDER_RENDERSYSTEM


#include <Windows.h>
#include "Mesh.h"
#include "Effect.h"

namespace Rain {
	namespace Render {
		class RenderComponent
		{
		public:
			int id;
			Mesh* s_mesh = nullptr;
			Effect* s_effect = nullptr;
		};
	}
}

#endif //RAIN_RENDERSYSTEM