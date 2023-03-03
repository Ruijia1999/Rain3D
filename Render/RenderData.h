#ifndef RAIN_RENDER_RENDERDATA
#define RAIN_RENDER_RENDERDATA
#include "Mesh.h"
#include "Effect.h"
#include "Texture.h"
#include "ConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "RenderDataBase.h"
#include <memory>
namespace Rain {
	namespace Render {
		struct RenderData:RenderDataBase
		{
			RenderData();
			RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> normalMap, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer);
			RenderData(const std::shared_ptr<Mesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> normalMap, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer, const ConstantBufferFormats::FrameConstantBuffer& i_frameBuffer);
			~RenderData();
			void Draw();
			const std::shared_ptr<Mesh> mesh;
			const std::shared_ptr <Effect> effect;
			const std::shared_ptr <Texture> texture;
			const std::shared_ptr <Texture> normalMap;
			ConstantBufferFormats::VSConstantBuffer constantBuffer;
			ConstantBufferFormats::FrameConstantBuffer frameBuffer;
		};
	}
}
#endif // !RAIN_GRAPHICS_RENDERDATA

