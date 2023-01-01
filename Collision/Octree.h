#ifndef Rain_COLLISION_OCTREE_H
#define Rain_COLLISION_OCTREE_H

#include "OctreeNode.h"
#include "ColliderBase.h"

namespace Rain {
	namespace Collision {
		class Octree
		{
		public:
			OctreeNode* root;
			Octree();
			void Check();
			void Insert(const ColliderBase* colliderBase);

		};
	}
}


#endif
