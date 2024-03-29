#ifndef RAIN_RENDER_SKELETALMESH
#define RAIN_RENDER_SKELETALMESH


#include "windows/windows.h"
#include "RenderFormats.h"
#include "Skeleton.h"
#include "Animation\Pose.h"
#include <string>
namespace Rain {
	namespace Render {
		struct JointData {
			char name[52];
			double translation[3];
			double rotation[3];
			double jointRotation[3];
			int childrenCount;
			int* children;
		};

		class SkeletalMesh
		{
		private:

			ID3D11Buffer* m_indexBuffer = nullptr;
			
		public:
			Skeleton* skeleton;

			void Initialize(const char* i_filePath);
			void Draw(Animation::Pose* pose) const;
			void CleanUp();
			
			void UpdateMesh(Animation:: Pose* pose, ID3D11Buffer*& i_vertexBuffer)const;
			void UpdatePoseTransform(const Joint* joint, int parentIndex, Joint** jointArray, int index, Animation::Pose* pose) const;

			SkeletalMesh(const SkeletalMesh& i_mesh);
			SkeletalMesh();
			~SkeletalMesh() {
			
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
			IndexFormat* indexData = nullptr;
			SkeletalVertexFormat* vertexData = nullptr;
			
		private:
			void Load(int& i_indexCount, int& i_pointCount, Skeleton* skeleton, IndexFormat*& i_indexData, SkeletalVertexFormat*& i_vertexData);

		};
	}
}

#endif //RAIN_RENDER_SKELETALMESH