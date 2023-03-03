#ifndef RAIN_RENDER_RENDERDATABASE
#define RAIN_RENDER_RENDERDATABASE
#include "Mesh.h"
#include "Effect.h"
#include "Texture.h"
#include "ConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include <memory>

enum RenderDataType {
	StaticMesh,
	SkeletalMesh,
	None,
};
namespace Rain {
	namespace Render {
		struct RenderDataBase
		{
		public:
			RenderDataBase() {
				type = RenderDataType::None;
			}
			RenderDataBase(RenderDataType i_type) {
				type = i_type;
			}

			RenderDataType type;
			virtual void Draw() = 0;
		};
	}
}
#endif // !RAIN_GRAPHICS_RENDERDATABASE

