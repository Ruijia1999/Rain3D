
#include "SphereCollider.h"
#include "Collision.h"
#include "Math/Quaternion.h"
Rain::Collision::SphereCollider::SphereCollider(Math::Quaternion i_rot, Math::Vector3 i_pos, float r): ColliderBase() {
	radius = r;
	pos = i_pos;
	rot = i_rot;
}
Rain::Collision::SphereCollider::SphereCollider(Math::Quaternion i_rot, Math::Vector3 i_pos, const Rain::Render::Mesh* i_mesh): ColliderBase() {
	pos = i_pos;
	rot = i_rot;

	Collision::GetSize(i_mesh->vertexCount, i_mesh->vertexData, radius);
}
void Rain::Collision::SphereCollider::SetSize(float r) {
	radius = r;
}

void Rain::Collision::SphereCollider::Update(Math::Quaternion i_rot, Math::Vector3 i_pos) {
	pos = i_pos;
	rot = i_rot;
}
