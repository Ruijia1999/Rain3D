#ifndef RAIN_RENDER_RENDERDATA
#define RAIN_RENDER_RENDERDATA
#include "Mesh.h"
#include "Effect.h"
#include "ConstantBuffer.h"
#include <memory>
namespace Rain {
	namespace Render {
		struct RenderData
		{
			RenderData();
			RenderData(const Mesh* i_mesh, const Effect* i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer);
			~RenderData();
			const Mesh* mesh;
			const Effect* effect;
			ConstantBuffer::VSConstantBuffer constantBuffer;
		};
	}
}
#endif // !RAIN_GRAPHICS_RENDERDATA

