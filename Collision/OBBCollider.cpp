#include "OBBCollider.h"
#include "Render/Mesh.h"
#include "Collision.h"
Rain::Collision::OBBCollider::OBBCollider(Math::Quaternion rot, Math::Vector3 pos, Math::Vector3 scale, const Render::Mesh* i_mesh) :ColliderBase() {


	Collision::GetSize(scale, i_mesh->vertexCount, i_mesh->vertexData, size[0], size[1], size[2]);
	this->rot = rot;
	this->pos = pos;



}
Rain::Collision::OBBCollider::OBBCollider(Math::Quaternion rot, Math::Vector3 pos, float hX, float hY, float hZ):ColliderBase() {

	size[0] = hX;
	size[1] = hY;
	size[2] = hZ;

	this->rot = rot;
	this->pos = pos;

}

void Rain::Collision::OBBCollider::SetSize(float hX, float hY, float hZ) {
	size[0] = hX;
	size[1] = hY;
	size[2] = hZ;
}

Rain::Math::Vector3 Rain::Collision::OBBCollider::GetSize() {
	return Math::Vector3(size[0], size[1], size[2]);
}

void Rain::Collision::OBBCollider::Update(Math::Quaternion rot, Math::Vector3 pos) {
	this->pos = pos;
	this->rot = rot;
}