#ifndef RAIN_COLLISION
#define RAIN_COLLISION
#include "ECS\ComponentBase.h"
#include "ColliderBase.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "OBBCollider.h"
#include "Render\Mesh.h"
namespace Rain {
	namespace Collision
	{
		enum class ColliderType
		{
			AABB,
			OBB,
			Sphere,
			None
		};
		

		//helper
		//--------------

		bool BoxBox(const AABBCollider* i_collider0, const AABBCollider* i_collider1, const uint64_t i_timeSinceLastFrame);
		bool BoxSphere(const AABBCollider* i_collider0, const SphereCollider* i_collider1, const uint64_t i_timeSinceLastFrame);
		bool SphereSphere(const SphereCollider* i_collider0, const SphereCollider* i_collider1, const uint64_t i_timeSinceLastFrame);

		bool BoxBoxOBB(const AABBCollider* i_collider0, const OBBCollider* i_collider1, const uint64_t i_timeSinceLastFrame);
		bool BoxOBBBoxOBB(const OBBCollider* i_collider0, const OBBCollider* i_collider1, const uint64_t i_timeSinceLastFrame);
		bool BoxSphereOBB(const OBBCollider* i_collider0, const SphereCollider* i_collider1, const uint64_t i_timeSinceLastFrame);
		void GetSize(const int vertexCount, const Render::VertexFormat* vertexData, float& outX, float& outY, float& outZ);
		void GetSize(const int vertexCount, const Render::VertexFormat* vertexData, float& outRadius);
	};
}


#endif // !RAIN_COLLIDERSYSTEM


