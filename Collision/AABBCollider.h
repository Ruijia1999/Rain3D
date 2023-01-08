#ifndef Rain_COLLISION_AABBCOLLIDER_H
#define Rain_COLLISION_AABBCOLLIDER_H
#include "ColliderBase.h"
#include "Render\Mesh.h"
namespace Rain {
	namespace Collision {
		class AABBCollider: public ColliderBase
		{
		public:
			float size[3];
			AABBCollider(Math::Quaternion rot, Math::Vector3 pos, float hX = 0.5f, float hY = 0.5f, float hZ = 0.5f);
			AABBCollider(Math::Quaternion rot, Math::Vector3 pos, const Render::Mesh* i_mesh);
			void SetSize(float hX, float hY, float hZ);
			Math::Vector3 GetSize();

			void Update(Math::Quaternion rot, Math::Vector3 pos);
			void Initialize();
		};
	}
}

#endif
