#ifndef RAIN_RENDER_MESH
#define RAIN_RENDER_MESH


#include "windows/windows.h"

namespace Rain {
	namespace Render {
		struct VertexFormat {
			FLOAT x, y, z;
			FLOAT nx, ny, nz;
			FLOAT u,v;
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
			void Initialize(const char* i_filePath);
			void Draw() const;
			void CleanUp();

			const char* m_name;

		
			//helper
			//--------
			int vertexCount;
			int indexCount;
			VertexFormat* vertexData = nullptr;
			IndexFormat* indexData = nullptr;
			void Load(int& i_vertexCount, int& i_indexCount, VertexFormat*& i_vertexData, IndexFormat*& i_indexData);
		};
	}
}

#endif //RAIN_RENDER_MESH