#ifndef RAIN_RENDER_SKELETALMESH
#define RAIN_RENDER_SKELETALMESH


#include "windows/windows.h"
#include "RenderFormats.h"
#include "Skeleton.h"
#include <string>
namespace Rain {
	namespace Render {


		class SkeletalMesh
		{
		private:
			ID3D11Buffer* m_vertexBuffer = nullptr;
			ID3D11Buffer* m_indexBuffer = nullptr;
			
		public:

			void Initialize(const char* i_filePath);
			void Draw() const;
			void CleanUp();
			SkeletalMesh(const SkeletalMesh& i_mesh);
			SkeletalMesh();
			~SkeletalMesh() {
				m_vertexBuffer = nullptr;
				m_indexBuffer = nullptr;
				delete vertexData;
				delete indexData;
			}
			SkeletalMesh& operator=(const SkeletalMesh& i_mesh);
			std::string m_name;

			//helper
			//--------
			int pointCount;
			int indexCount;
			Skeleton* skeleton;
			IndexFormat* indexData = nullptr;
			SkeletalVertexFormat* vertexData = nullptr;
			
			void Load(int& i_indexCount, int& i_pointCount, Skeleton* skeleton, IndexFormat*& i_indexData);
		};
	}
}

#endif //RAIN_RENDER_SKELETALMESH