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
			//Math::Vector3 scale;
			//Math::Quaternion rotateOrient;
			//Math::Quaternion rotate;
			
			//Math::Vector3 parentScaleInverse;
			//Math::Vector3 translation;
			//
			
		public:
			Joint() {

			}
			Joint(Math::Matrix i_transformMatrix, std::vector<int>& i_children) {
				children.resize(i_children.size());
				children.swap(i_children);

			}



			Math::Quaternion jointOrient;
			std::vector<int> children;
			std::string name;
		};
	}
}
#endif // !RAIN_RENDER_JOINT

