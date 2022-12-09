#ifndef RAIN_RENDER_MESH
#define RAIN_RENDER_MESH


#include "windows/windows.h"

namespace Rain {
	namespace Render {
		struct VertexFormat {
			FLOAT x, y, z;
		};
		struct IndexFormat {
			INT16 x, y, z;
		};

		class Mesh
		{
		private:
			ID3D11Buffer* m_vertexBuffer = nullptr;
			ID3D11Buffer* m_indexBuffer = nullptr;
		
		public:

			void Initialize();
			void Draw();
			void CleanUp();

		};
	}
}

#endif //RAIN_RENDER_MESH