#ifndef RAIN_RENDER_SKELETON
#define RAIN_RENDER_SKELETON

#include "Joint.h"
#include "Animation\Pose.h"
namespace Rain {
	namespace Render {
		
		struct SkinclusterData {
			int jointIndex;
			float weight;
		};

		struct Skincluster {
			SkinclusterData data[4];
		};
		struct SkinnedVertexData {
			Math::Vector3 position;
			Skincluster skincluster;
		};
		class Skeleton
		{
		public:
			Joint* rootJoint;

			int jointCount;
			Joint** jointArray;
			Animation::Pose* bindPose;
			int pointCount;
			SkinnedVertexData* vertexInfo;

			void UpdateJointsPosition();
			Math::Vector3 GetPositionByIndex(int i_index);

		
		private:
			//helper------
			void UpdateSingleJointPosition(Joint* joint, Joint* parentJoint, int index, int parentIndex);
		};

	}
}

#endif
