#ifndef RAIN_RENDER_SKELETON
#define RAIN_RENDER_SKELETON

#include "Joint.h"

namespace Rain {
	namespace Render {
		struct SkinclusterData {
			int jointIndex;
			float weight;
		};

		struct Skincluster {
			SkinclusterData data[4];
		};

		class Skeleton
		{
		public:
			Joint* rootJoint;

			int jointCount;
			Joint* jointArray;

			int pointCount;
			Skincluster* skinclusterInfo;
		};

	}
}

#endif
