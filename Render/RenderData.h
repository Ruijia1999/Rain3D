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
			RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer);
			~RenderData();
			const std::shared_ptr<Mesh> mesh;
			const std::shared_ptr <Effect> effect;
			ConstantBuffer::VSConstantBuffer constantBuffer;
		};
	}
}
#endif // !RAIN_GRAPHICS_RENDERDATA

