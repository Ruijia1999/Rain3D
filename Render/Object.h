#ifndef RAIN_RENDER_OBJECT
#define RAIN_RENDER_OBJECT
#include "RenderData.h"
#include "Mesh.h"
#include "Effect.h"
#include "ConstantBuffer.h"
namespace Rain {
	namespace Render {
		class Object : public RenderData
		{
		public:
			Object();
			Object(const Mesh* i_mesh, const Effect* i_effect, const ConstantBuffer::VSConstantBuffer i_constantBuffer);
			const Mesh* mesh;
			const Effect* effect;
			ConstantBuffer::VSConstantBuffer constantBuffer;
			void Draw();
		};
	}
}




#endif // !RAIN_UI_TEXT
