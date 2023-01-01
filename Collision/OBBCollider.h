#ifndef Rain_COLLISION_OBBCOLLIDER_H
#define Rain_COLLISION_OBBCOLLIDER_H

#include "ColliderBase.h"

namespace Rain {
	namespace Collision {
		class OBBCollider : public ColliderBase
		{
		public:
			float size[3];

			OBBCollider(Math::Quaternion rot, Math::Vector3 pos, float hX = 0.5f, float hY = 0.5f, float hZ = 0.5f);

			void SetSize(float hX, float hY, float hZ);
			Math::Vector3 GetSize();
			void Update(Math::Quaternion rot, Math::Vector3 pos);
		};
	}
}

#endif
