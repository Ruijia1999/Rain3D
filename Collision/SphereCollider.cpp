#ifndef Rain_COLLISION_SPHERECOLLIDER_H
#define Rain_COLLISION_SPHERECOLLIDER_H

#include "SphereCollider.h"


Rain::Collision::SphereCollider::SphereCollider(Math::Quaternion rot, Math::Vector3 pos, float r): ColliderBase() {
	radius = r;
}

void Rain::Collision::SphereCollider::SetSize(float r) {
	radius = r;
}
float Rain::Collision::SphereCollider::GetSize() const{
	return radius;
}

void Rain::Collision::SphereCollider::Update(Math::Quaternion rot, Math::Vector3 pos) {
	this->pos = pos;
}
#endif
