#include "Collision.h"
#include "Math\Vector3.h"
#include "Math\Quaternion.h"
#include "Math\Math.h"
using namespace Rain::Math;

bool Rain::Collision::BoxBox(const AABBCollider* i_collider0, const AABBCollider* i_collider1, const uint64_t i_timeSinceLastFrame) {
	Math::Vector3 pos0 = i_collider0->pos;
	Math::Vector3 pos1 = i_collider1->pos;

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

bool Rain::Collision::BoxSphere(const AABBCollider* i_collider0, const SphereCollider* i_collider1, const uint64_t i_timeSinceLastFrame) {
	Math::Vector3 pos0 = i_collider0->pos;
	Math::Vector3 pos1 = i_collider1->pos;

	if (abs(i_collider0->size[1] + i_collider1->radius) < abs(pos0.y - pos1.y)) {
		return false;
	}
	if (abs(i_collider0->size[0] + i_collider1->radius) < abs(pos0.x - pos1.x)) {
		return false;
	}
	if (abs(i_collider0->size[2] + i_collider1->radius) < abs(pos0.z - pos1.z)) {
		return false;
	}
	return true;
}

bool Rain::Collision::SphereSphere(const Collision::SphereCollider* i_collider0, const Collision::SphereCollider* i_collider1, const uint64_t i_timeSinceLastFrame) {

	float distance = (i_collider0->pos - i_collider1->pos).GetLength();

	if (i_collider0->radius + i_collider1->radius > distance) {
		return true;
	}
	return false;
}

bool Rain::Collision::BoxBoxOBB(const AABBCollider* i_collider0, const OBBCollider* i_collider1, const uint64_t i_timeSinceLastFrame) {

	Math::Vector3 pos0 = i_collider0->pos;
	Math::Vector3 pos1 = i_collider1->pos;
	Math::Vector3 distance = pos1 - pos0;

	Math::Vector3 X0 = Math::Vector3(1, 0, 0);
	Math::Vector3 Y0 = Math::Vector3(0, 1, 0);
	Math::Vector3 Z0 = Math::Vector3(0, 0, 1);

	Math::Vector3 X1 = i_collider1->rot * Math::Vector3(1, 0, 0);
	Math::Vector3 Y1 = i_collider1->rot * Math::Vector3(0, 1, 0);
	Math::Vector3 Z1 = i_collider1->rot * Math::Vector3(0, 0, 1);

	Math::Vector3 Box0Vec[3]{ X0 , Y0, Z0 };
	Math::Vector3 Box1Vec[3]{ X1 , Y1, Z1 };
	//Box0
	for (int i = 0; i < 3; i++) {
		float r = abs(Dot(distance, Box0Vec[i]));
		float a = i_collider0->size[i];
		float b = abs(i_collider1->size[0] * Dot(Box1Vec[0], Box0Vec[i])) + abs(i_collider1->size[1] * Dot(Box1Vec[1], Box0Vec[i])) + abs(i_collider1->size[2] * Dot(Box1Vec[2], Box0Vec[i]));
		if (r > a + b) {
			return false;
		}
	}
	//Box1
	for (int i = 0; i < 3; i++) {
		float r = abs(Dot(distance, Box1Vec[i]));
		float a = abs(i_collider0->size[0] * Dot(Box0Vec[0], Box1Vec[i])) + abs(i_collider0->size[1] * Dot(Box0Vec[1], Box1Vec[i])) + abs(i_collider0->size[2] * Dot(Box0Vec[2], Box1Vec[i]));
		float b = i_collider1->size[i];
		if (r > a + b) {
			return false;
		}
	}
	return true;
}
bool Rain::Collision::BoxOBBBoxOBB(const OBBCollider* i_collider0, const OBBCollider* i_collider1, const uint64_t i_timeSinceLastFrame) {

	Math::Vector3 pos0 = i_collider0->pos;
	Math::Vector3 pos1 = i_collider1->pos;
	Math::Vector3 distance = pos1 - pos0;

	Math::Vector3 X0 = i_collider0->rot * Math::Vector3(1, 0, 0);
	Math::Vector3 Y0 = i_collider0->rot * Math::Vector3(0, 1, 0);
	Math::Vector3 Z0 = i_collider0->rot * Math::Vector3(0, 0, 1);

	Math::Vector3 X1 = i_collider1->rot * Math::Vector3(1, 0, 0);
	Math::Vector3 Y1 = i_collider1->rot * Math::Vector3(0, 1, 0);
	Math::Vector3 Z1 = i_collider1->rot * Math::Vector3(0, 0, 1);

	Math::Vector3 Box0Vec[3]{ X0 , Y0, Z0 };
	Math::Vector3 Box1Vec[3]{ X1 , Y1, Z1 };
	//Box0
	for (int i = 0; i < 3; i++) {
		float r = abs(Dot(distance, Box0Vec[i]));
		float a = i_collider0->size[i];
		float b = abs(i_collider1->size[0] * Dot(Box1Vec[0], Box0Vec[i])) + abs(i_collider1->size[1] * Dot(Box1Vec[1], Box0Vec[i])) + abs(i_collider1->size[2] * Dot(Box1Vec[2], Box0Vec[i]));
		if (r > a + b) {
			return false;
		}
	}
	//Box1
	for (int i = 0; i < 3; i++) {
		float r = abs(Dot(distance, Box1Vec[i]));
		float a = abs(i_collider0->size[0] * Dot(Box0Vec[0], Box1Vec[i])) + abs(i_collider0->size[1] * Dot(Box0Vec[1], Box1Vec[i])) + abs(i_collider0->size[2] * Dot(Box0Vec[2], Box1Vec[i]));
		float b = i_collider1->size[i];
		if (r > a + b) {
			return false;
		}
	}
	//9 Cross Product
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Math::Vector3 normal = Cross(Box0Vec[i], Box1Vec[j]);
			float r = abs(Dot(distance, normal));
			float a = abs(i_collider0->size[0] * Dot(Box0Vec[0], normal)) + abs(i_collider0->size[1] * Dot(Box0Vec[1], normal)) + abs(i_collider0->size[2] * Dot(Box0Vec[2], normal));
			float b = abs(i_collider1->size[0] * Dot(Box1Vec[0], normal)) + abs(i_collider1->size[1] * Dot(Box1Vec[1], normal)) + abs(i_collider1->size[2] * Dot(Box1Vec[2], normal));
			if (r > a + b) {
				return false;
			}
		}
	}
	return true;
}

bool Rain::Collision::BoxSphereOBB(const OBBCollider* i_collider0, const SphereCollider* i_collider1, const uint64_t i_timeSinceLastFrame) {

	Math::Vector3 pos0 = i_collider0->pos;
	Math::Vector3 pos1 = i_collider1->pos;
	Math::Vector3 distance = pos1 - pos0;

	Math::Vector3 X0 = i_collider0->rot * Math::Vector3(1, 0, 0);
	Math::Vector3 Y0 = i_collider0->rot * Math::Vector3(0, 1, 0);
	Math::Vector3 Z0 = i_collider0->rot * Math::Vector3(0, 0, 1);

	Math::Vector3 Box0Vec[3]{ X0 , Y0, Z0 };

	for (int i = 0; i < 3; i++) {
		float r = abs(Dot(distance, Box0Vec[i]));
		float a = i_collider0->size[i];
		float b = i_collider1->radius;
		if (r > a + b) {
			return false;
		}
	}
	return true;
}
void Rain::Collision::GetSize(const int vertexCount, const Render::StaticVertexFormat* vertexData, float& outX, float& outY, float& outZ) {
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;

	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
	for (int i = 0; i < vertexCount; i++) {
		minX = min(vertexData[i].x, minX);
		minY = min(vertexData[i].y, minY);
		minZ = min(vertexData[i].z, minZ);
		maxX = max(vertexData[i].x, maxX);
		maxY = max(vertexData[i].y, maxY);
		maxZ = max(vertexData[i].z, maxZ);
	}
	outX = max(abs(minX), abs(maxX));
	outY = max(abs(minY), abs(maxY));
	outZ = max(abs(minZ), abs(maxZ));
}

void Rain::Collision::GetSize(const int vertexCount, const Render::StaticVertexFormat* vertexData, float& outRadius) {

	float maxRadius = FLT_MIN;
	float radius = 0;
	for (int i = 0; i < vertexCount; i++) {
		radius = vertexData[i].x * vertexData[i].x  +vertexData[i].y * vertexData[i].y  +vertexData[i].z * vertexData[i].z;
		maxRadius = max(radius, maxRadius);
	}
	outRadius = sqrtf(maxRadius);

}