#ifndef RAIN_RENDER_MESH
#define RAIN_RENDER_MESH


#include "windows/windows.h"
#include "RenderFormats.h"
#include <string>
namespace Rain {
	namespace Render {
		

		class Mesh
		{
		private:
			ID3D11Buffer* m_vertexBuffer = nullptr;
			ID3D11Buffer* m_indexBuffer = nullptr;
		
		public:

			void Initialize(const char* i_filePath);
			void Draw() const;
			void CleanUp();
			Mesh(const Mesh& i_mesh);
			Mesh();
			~Mesh() {
				m_vertexBuffer = nullptr;
				m_indexBuffer = nullptr;
				delete vertexData;
				delete indexData;
			}
			Mesh& operator=(const Mesh& i_mesh);
			std::string m_name;

			//helper
			//--------
			int vertexCount;
			int indexCount;
			StaticVertexFormat* vertexData = nullptr;
			IndexFormat* indexData = nullptr;
			void Load(int& i_vertexCount, int& i_indexCount, StaticVertexFormat*& i_vertexData, IndexFormat*& i_indexData);
		};
	}
}

#endif //RAIN_RENDER_MESH