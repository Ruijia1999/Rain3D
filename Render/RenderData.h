#ifndef RAIN_RENDER_RENDERDATA
#define RAIN_RENDER_RENDERDATA
#include "Mesh.h"
#include "Effect.h"
#include "ConstantBuffer.h"
namespace Rain {
	namespace Render {
		struct RenderData
		{
			RenderData();
			RenderData(Mesh* i_mesh, Effect* i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer);
			Mesh* mesh;
			Effect* effect;
			ConstantBuffer::VSConstantBuffer constantBuffer;
		};
	}
}
#endif // !RAIN_GRAPHICS_RENDERDATA

