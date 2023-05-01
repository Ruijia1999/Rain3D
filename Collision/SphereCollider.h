#ifndef Rain_COLLISION_SPHERECOLLIDER_H
#define Rain_COLLISION_SPHERECOLLIDER_H

#include "ColliderBase.h"
#include "Render/Mesh.h"
namespace Rain {
	namespace Collision {
		class SphereCollider: public ColliderBase
		{
		public:
			SphereCollider(Math::Quaternion rot, Math::Vector3 pos, float r = 0.5f);
			SphereCollider(Math::Quaternion rot, Math::Vector3 pos, Math::Vector3 scale, const Render::Mesh* i_mesh);
			void SetSize(float r);
			void Update(Math::Quaternion rot, Math::Vector3 pos);
			float radius;
		};
	}
}

#endif