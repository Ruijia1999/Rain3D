#include "AABBCollider.h"
#include "Collision.h"
Rain::Collision::AABBCollider::AABBCollider(Math::Quaternion rot, Math::Vector3 pos, Math::Vector3 scale, const Render::Mesh* i_mesh) :ColliderBase() {


	Collision::GetSize(scale, i_mesh->vertexCount, i_mesh->vertexData, size[0], size[1], size[2]);
	this->rot = rot;
	this->pos = pos;

	Initialize();



}
Rain::Collision::AABBCollider::AABBCollider(Math::Quaternion rot, Math::Vector3 pos, float hX, float hY, float hZ):ColliderBase() {

	size[0] = hX;
	size[1] = hY;
	size[2] = hZ;
	
	this->rot = rot;
	this->pos = pos;

	Initialize();
	
}

void Rain::Collision::AABBCollider::SetSize(float hX, float hY, float hZ) {
	size[0] = hX;
	size[1] = hY;
	size[2] = hZ;
}

Rain::Math::Vector3 Rain::Collision::AABBCollider::GetSize() {
	return Math::Vector3(size[0], size[1], size[2]);
}
void Rain::Collision::AABBCollider::Initialize() {
	//Get the AABB Box

	Math::Quaternion quaternion = rot;

	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;

	Math::Vector3 vec1 = Math::Vector3(size[0], size[1], size[2]);
	vec1 = quaternion * vec1;
	if (vec1.x < minX) minX = vec1.x;
	if (vec1.y < minY) minY = vec1.y;
	if (vec1.z < minZ) minZ = vec1.z;

	Math::Vector3 vec2 = Math::Vector3(size[0], size[1], -size[2]);
	vec2 = quaternion * vec2;
	if (vec2.x < minX) minX = vec2.x;
	if (vec2.y < minY) minY = vec2.y;
	if (vec2.z < minZ) minZ = vec2.z;

	Math::Vector3 vec3 = Math::Vector3(size[0], -size[1], size[2]);
	vec3 = quaternion * vec3;
	if (vec3.x < minX) minX = vec3.x;
	if (vec3.y < minY) minY = vec3.y;
	if (vec3.z < minZ) minZ = vec3.z;

	Math::Vector3 vec4 = Math::Vector3(size[0], -size[1], -size[2]);
	vec4 = quaternion * vec4;
	if (vec4.x < minX) minX = vec4.x;
	if (vec4.y < minY) minY = vec4.y;
	if (vec4.z < minZ) minZ = vec4.z;

	Math::Vector3 vec5 = Math::Vector3(-size[0], size[1], size[2]);
	vec5 = quaternion * vec5;
	if (vec5.x < minX) minX = vec5.x;
	if (vec5.y < minY) minY = vec5.y;
	if (vec5.z < minZ) minZ = vec5.z;

	Math::Vector3 vec6 = Math::Vector3(-size[0], size[1], -size[2]);
	vec6 = quaternion * vec6;
	if (vec6.x < minX) minX = vec6.x;
	if (vec6.y < minY) minY = vec6.y;
	if (vec6.z < minZ) minZ = vec6.z;

	Math::Vector3 vec7 = Math::Vector3(-size[0], -size[1], size[2]);
	vec7 = quaternion * vec7;
	if (vec7.x < minX) minX = vec7.x;
	if (vec7.y < minY) minY = vec7.y;
	if (vec7.z < minZ) minZ = vec7.z;

	Math::Vector3 vec8 = Math::Vector3(-size[0], -size[1], -size[2]);
	vec8 = quaternion * vec8;
	if (vec8.x < minX) minX = vec8.x;
	if (vec8.y < minY) minY = vec8.y;
	if (vec8.z < minZ) minZ = vec8.z;

	size[0] = abs(minX);
	size[1] = abs(minY);
	size[2] = abs(minZ);
}
void Rain::Collision::AABBCollider::Update(Math::Quaternion rot, Math::Vector3 pos) {
	this->pos = pos;
	this->rot = rot;
}