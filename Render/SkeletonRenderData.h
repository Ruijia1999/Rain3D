#ifndef RAIN_RENDER_SKELETONRENDERDATA
#define RAIN_RENDER_SKELETONRENDERDATA
#include "SkeletalMesh.h"
#include "Effect.h"
#include "Texture.h"
#include "ConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "RenderDataBase.h"
#include <memory>
namespace Rain {
	namespace Render {
		struct SkeletonRenderData :RenderDataBase
		{
			SkeletonRenderData();
			SkeletonRenderData(const std::shared_ptr<SkeletalMesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer, const ConstantBufferFormats::FrameConstantBuffer& i_frameBuffer);
			//SkeletonRenderData(const std::shared_ptr<SkeletalMesh>& i_mesh, const std::shared_ptr <Effect>& i_effect, const std::shared_ptr <Texture>& i_texture, std::shared_ptr <Texture> normalMap, const ConstantBufferFormats::VSConstantBuffer& i_constantBuffer, const ConstantBufferFormats::FrameConstantBuffer& i_frameBuffer);
			~SkeletonRenderData();
			void Draw();
			const std::shared_ptr<SkeletalMesh> mesh;
			const std::shared_ptr <Effect> effect;
			const std::shared_ptr <Texture> texture;
			const std::shared_ptr <Texture> normalMap;
			ConstantBufferFormats::VSConstantBuffer constantBuffer;
			ConstantBufferFormats::FrameConstantBuffer frameBuffer;
		};
	}
}
#endif // !RAIN_GRAPHICS_SkeletonRenderData

