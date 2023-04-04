#ifndef RAIN_RENDER_JOINT
#define RAIN_RENDER_JOINT
#include "Math\Math.h"
#include <vector>
#include <string>
#include <functional>
namespace Rain {
	namespace Render {
		class Joint
		{
		public:
			Math::Vector3 scale;
			Math::Quaternion rotateOrient;
			Math::Quaternion rotate;
			Math::Quaternion jointOrient;
			Math::Vector3 parentScaleInverse;
			Math::Vector3 translation;
			
			
		public:
			Joint() {
				scale = Math::Vector3(1, 1, 1);
				transformMatrix = Math::Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			}
			Joint(Math::Matrix i_transformMatrix, std::vector<int>& i_children) {
				transformMatrix = i_transformMatrix;
				children.resize(i_children.size());
				children.swap(i_children);
				worldPosition = Math::Vector4(0, 0, 0,0);
				scale = Math::Vector3(1, 1, 1);
			}

			Math::Matrix transformMatrix;
			Math::Vector4 worldPosition;
			std::vector<int> children;
			std::string name;
		};
	}
}
#endif // !RAIN_RENDER_JOINT

