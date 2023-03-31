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
			std::string name;
			Math::Vector3 scale;
			Math::Quaternion rotateOrient;
			Math::Vector3 rotate;
			Math::Quaternion jointOrient;
			Math::Vector3 parentScaleInverse;
			Math::Vector3 translation;

			
		public:
			Joint() {
				transformMatrix = Math::Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			}
			Joint(Math::Matrix i_transformMatrix, std::vector<int>& i_children) {
				transformMatrix = i_transformMatrix;
				children.resize(i_children.size());
				children.swap(i_children);
			}

			Math::Matrix transformMatrix;
			std::vector<int> children;
		};
	}
}
#endif // !RAIN_RENDER_JOINT

