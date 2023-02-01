#ifndef RAIN_RENDER_RENDERDATA
#define RAIN_RENDER_RENDERDATA
#include "Mesh.h"
#include "Effect.h"
#include "Texture.h"
#include "ConstantBuffer.h"
#include <memory>
namespace Rain {
	namespace Render {
		struct RenderData
		{
			RenderData();
			RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> normalMap, const ConstantBuffer::VSConstantBuffer& i_constantBuffer);
			RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> normalMap, const ConstantBuffer::VSConstantBuffer& i_constantBuffer, const ConstantBuffer::FrameConstantBuffer& i_frameBuffer);
			~RenderData();
			const std::shared_ptr<Mesh> mesh;
			const std::shared_ptr <Effect> effect;
			const std::shared_ptr <Texture> texture;
			const std::shared_ptr <Texture> normalMap;
			ConstantBuffer constantBuffer;
			ConstantBuffer frameBuffer;
		};
	}
}
#endif // !RAIN_GRAPHICS_RENDERDATA

