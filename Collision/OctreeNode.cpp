#include "OctreeNode.h"


#define LeftBottomBack 0
#define LeftBottomFront 1
#define LeftTopBack 2
#define LeftTopFront 3
#define RightBottomBack 4
#define RightBottomFront 5
#define RightTopBack 6
#define RightTopFront 7

Rain::Collision::OctreeNode::OctreeNode(float i_minX, float i_maxX, float i_minY, float i_maxY, float i_minZ, float i_maxZ, int i_index) {
	m_children = nullptr;
	m_capacity = 2;
	m_childrenAmount = 0;
	m_colliders = new const AABBCollider*[m_capacity];
	m_index = i_index;

	minX = i_minX;
	maxX = i_maxX;
	minY = i_minY;
	maxY = i_maxY;
	minZ = i_minZ;
	maxZ = i_maxZ;




}

void Rain::Collision::OctreeNode::Insert(const AABBCollider* i_collider) {
	if (m_childrenAmount < m_capacity) {
		m_colliders[m_childrenAmount++] = i_collider;
	}
	else {
		if (m_index>6) {
			Enlarge();
			m_colliders[m_childrenAmount++] = i_collider;
		}
		else {
			if (m_children == nullptr) {
				Split();
			}
			
			InsertChildren(i_collider);
		}
	}

}

void Rain::Collision::OctreeNode::Split() {
	m_children = new OctreeNode * [8];
	m_children[LeftBottomBack] = new OctreeNode(minX, (maxX + minX) / 2, minY, (maxY + minY) / 2, minZ, (maxZ + minZ) / 2, m_index+1);
	m_children[LeftBottomFront] = new OctreeNode(minX, (maxX + minX) / 2, minY, (maxY + minY) / 2, (maxZ + minZ) / 2, maxZ, m_index + 1);
	m_children[LeftTopBack] = new OctreeNode(minX, (maxX + minX) / 2, (maxY + minY) / 2, maxY, minZ, (maxZ + minZ) / 2, m_index + 1);
	m_children[LeftTopFront] = new OctreeNode(minX, (maxX + minX) / 2, (maxY + minY) / 2, maxY, (maxZ + minZ) / 2, maxZ, m_index + 1);
	m_children[RightBottomBack] = new OctreeNode((maxX + minX) / 2, maxX, minY, (maxY + minY) / 2, minZ, (maxZ + minZ) / 2, m_index + 1);
	m_children[RightBottomFront] = new OctreeNode((maxX + minX) / 2, maxX, minY, (maxY + minY) / 2, (maxZ + minZ) / 2, maxZ, m_index + 1);
	m_children[RightTopBack] = new OctreeNode((maxX + minX) / 2, maxX, (maxY + minY) / 2, maxY, minZ, (maxZ + minZ) / 2, m_index + 1);
	m_children[RightTopFront] = new OctreeNode((maxX + minX) / 2, maxX, (maxY + minY) / 2, maxY, (maxZ + minZ) / 2, maxZ, m_index + 1);

	for (int i = 0; i < m_capacity; i++) {
		InsertChildren(m_colliders[i]);
	}
}
void Rain::Collision::OctreeNode::InsertChildren(const AABBCollider* collider) {


	for (int i = 0; i < 8; i++) {
		if (IsIntersect(collider,m_children[i])) {
			m_children[i]->Insert(collider);
		}
	}
	

	
}

void Rain::Collision::OctreeNode::Enlarge() {

	
	m_capacity *= 2;
	const AABBCollider** newColliders = new const AABBCollider * [m_capacity * 2];

	for (int i = 0; i < m_childrenAmount; i++) {
		newColliders[i] = m_colliders[i];
	}
	delete(m_colliders);
	m_colliders = newColliders;
}

bool Rain::Collision::OctreeNode::IsIntersect(const AABBCollider* colliderBase, const OctreeNode* treeNode) {
	Math::Vector3 pos0 = colliderBase->pos;
	Math::Vector3 pos1 = Math::Vector3((treeNode->maxX+treeNode->minX)/2, (treeNode->maxY + treeNode->minY) / 2, (treeNode->maxZ + treeNode->minZ) / 2);
	
	if (abs(colliderBase->size[1] + (treeNode->maxY - treeNode->minY) / 2) < abs(pos0.y - pos1.y)) {
		return false;
	}
	if (abs(colliderBase->size[0] + (treeNode->maxX - treeNode->minX) / 2) < abs(pos0.x - pos1.x)) {
		return false;
	}
	if (abs(colliderBase->size[2] + (treeNode->maxZ - treeNode->minZ) / 2) < abs(pos0.z - pos1.z)) {
		return false;
	}
	return true;
}

bool Rain::Collision::OctreeNode::IsIntersect(const AABBCollider* i_collider0, const AABBCollider* i_collider1) {
	Math::sVector pos0 = i_collider0->rigidBodyState->position;
	Math::sVector pos1 = i_collider1->rigidBodyState->position;

	if (abs(i_collider0->size[1] + i_collider1->size[1]) < abs(pos0.y - pos1.y)) {
		return false;
	}
	if (abs(i_collider0->size[0] + i_collider1->size[0]) < abs(pos0.x - pos1.x)) {
		return false;
	}
	if (abs(i_collider0->size[2] + i_collider1->size[2]) < abs(pos0.z - pos1.z)) {
		return false;
	}

	return true;
}

void Rain::Collision::OctreeNode::Check() {
	if (m_children == nullptr) {
		for (int i = 0; i < m_childrenAmount; i++) {
			
			for (int j = 0; j < m_childrenAmount; j++) {
				if (j != i) {
					if (IsIntersect(m_colliders[i], m_colliders[j])) {
						m_colliders[i]->Inters(m_colliders[j]);
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			m_children[i]->Check();
		}
	}
}