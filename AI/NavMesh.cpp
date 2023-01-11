#include "NavMesh.h"

#pragma region Polygon
Rain::AI::Polygon::Polygon() {

}
Rain::AI::Polygon::Polygon(std::vector<Math::Vector2> i_vertices) {
	vertices.resize(i_vertices.size());
	swap(vertices, i_vertices);
	center = GetCenter();
	int q;
}

void Rain::AI::Polygon::GenerateConvexPolygons(std::vector<Polygon>& convexPolygons) {
	//Find out concave vertices
	int count = vertices.size();
	bool isConvex = true;
	for (int i = 0; i < count; i++) {
		if (IsConcave(i)) {
			//Find out a diagonal in the polygon
			int partition = FindDiagonal(i);
			isConvex = false;
			PartitionDiagonal(i, partition, convexPolygons);
			break;
		}
	}
	if (isConvex) {
		convexPolygons.push_back(Polygon(vertices));
	}
}

Rain::Math::Vector2 Rain::AI::Polygon::GetCenter() {
	int count = vertices.size();
	Math::Vector2 center(0, 0);
	for (int i = 0; i < count; i++) {
		center = center + vertices[i] / count;
	}
	return center;
}

//helpers
//-----------------------
bool Rain::AI::Polygon::IsConcave(int i_index) {
	int count = vertices.size();
	int i = (i_index - 1) % count;
	Math::Vector2 vec1 = vertices[i_index] - vertices[(i_index - 1 + count) % count];
	Math::Vector2 vec2 = vertices[(i_index + 1) % count] - vertices[(i_index - 1 + count) % count];
	if ((vec1 ^ vec2) > 0) {
		return true;
	}
	else {
		return false;
	}
}

int Rain::AI::Polygon::FindDiagonal(int i_index) {
	int count = vertices.size();
	for (int i = 2; i < count - 1; i++) {
		if (IsInAngel(i_index, (i_index + i) % count) && !IsIntersected(i_index, (i_index + i) % count)) {
			return (i_index + i) % count;
		}
	}
	//Fail
	return -1;
}

void Rain::AI::Polygon::PartitionDiagonal(int i_index0, int i_index1, std::vector<Polygon>& convexPolygons) {
	int count = vertices.size();
	std::vector<Math::Vector2> verticesLeft;
	std::vector<Math::Vector2> verticesRight;
	if (i_index0 < i_index1) {
		for (int i = i_index0; i <= i_index1; i++) {
			verticesLeft.push_back(vertices[i]);
		}
		for (int i = i_index1; i <= i_index0 + count; i++) {
			verticesRight.push_back(vertices[i % count]);
		}
	}
	else {
		for (int i = i_index0; i <= i_index1 + count; i++) {
			verticesLeft.push_back(vertices[i % count]);
		}
		for (int i = i_index1; i <= i_index0; i++) {
			verticesRight.push_back(vertices[i]);
		}
	}
	Polygon left(verticesLeft);
	Polygon right(verticesRight);
	left.GenerateConvexPolygons(convexPolygons);
	right.GenerateConvexPolygons(convexPolygons);
}
bool Rain::AI::Polygon::IsInAngel(int i_index0, int i_index1) {
	int count = vertices.size();
	Math::Vector2 vec1 = vertices[i_index1] - vertices[(i_index0 - 1 + count) % count];
	Math::Vector2 vec2 = vertices[i_index0] - vertices[(i_index0 - 1 + count) % count];

	Math::Vector2 vec3 = vertices[i_index1] - vertices[i_index0];
	Math::Vector2 vec4 = vertices[(i_index0 + 1) % count] - vertices[i_index0];

	if ((vec1 ^ vec2) > 0 || (vec3 ^ vec4) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Rain::AI::Polygon::IsIntersected(int i_index0, int i_index1) {

	int count = vertices.size();
	Math::Vector2 vtc0 = vertices[i_index0];
	Math::Vector2 vtc1 = vertices[i_index1];
	int left = i_index1 - i_index0;

	for (int i = 0; i < count; i++) {
		if (IsIntersected(vtc0, vtc1, vertices[i], vertices[(i + 1) % count])) {
			return true;
		}
	}
	return false;
}

bool Rain::AI::Polygon::IsIntersected(Math::Vector2 vtc0, Math::Vector2 vtc1, Math::Vector2 vtc2, Math::Vector2 vtc3) {
	Math::Vector2 vec0 = vtc0 - vtc2;
	Math::Vector2 vec1 = vtc3 - vtc2;
	Math::Vector2 vec2 = vtc1 - vtc2;
	if ((vec0 ^ vec1) * (vec2 ^ vec1) >= 0) {
		return false;
	}
	vec0 = vtc2 - vtc0;
	vec1 = vtc1 - vtc0;
	vec2 = vtc3 - vtc0;
	if ((vec0 ^ vec1) * (vec2 ^ vec1) > 0) {
		return false;
	}

	return true;
}

#pragma endregion

void Rain::AI::NavMesh::GenerateNavMesh() {
	polygonData.GenerateConvexPolygons(convexPolygons);
	return;
}


