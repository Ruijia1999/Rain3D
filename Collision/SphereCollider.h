#include "ColliderBase.h"
namespace Rain {
	namespace Collision {
		class SphereCollider: public ColliderBase
		{
		public:
			SphereCollider(Math::Quaternion rot, Math::Vector3 pos, float r = 0.5f);
			void SetSize(float r);
			float GetSize() const;
			void Update(Math::Quaternion rot, Math::Vector3 pos);
		private:
			float radius;
		};
	}
}

