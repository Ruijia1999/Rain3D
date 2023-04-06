#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math\Matrix.h"
namespace Rain {
	namespace Animation {
		class Pose
		{
		public:
			int jointCount;
			Math::Vector3* transformation;
			Math::Quaternion* rotation;
			Math::Matrix* transformMatrix;
			Math::Vector4* worldPosition;
			Pose() {
				jointCount = 0;
				transformation = nullptr;
				rotation = nullptr;
				transformMatrix = nullptr;
				worldPosition = nullptr;
			}

			Pose(int i_jointCount) {
				jointCount = i_jointCount;
				transformation = new Math::Vector3[i_jointCount];
				rotation = new Math::Quaternion[i_jointCount];
				transformMatrix = new Math::Matrix[i_jointCount];
				worldPosition = new Math::Vector4[i_jointCount];
			}
		};
	}
}

