#include "Octree.h"
Rain::Collision::Octree::Octree() {
	root = new OctreeNode(-3,3,-3,3,-3,3,0);
}
void Rain::Collision::Octree::Check() {
	root->Check();
}
void Rain::Collision::Octree::Insert(const ColliderBase* colliderBase) {
	root->Insert((AABBCollider*)colliderBase);
}