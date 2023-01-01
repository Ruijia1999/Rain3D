#ifndef Rain_COLLISION_COLLIDERBASE

#include <functional>
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace Rain {
	namespace Collision {
		

		class ColliderBase
		{
		public:
			Math::Vector3 pos;
			Math::Quaternion rot;
			ColliderBase();
			virtual void Update(Math::Quaternion rot, Math::Vector3 pos) = 0;

			
		};
	}
}

#endif
