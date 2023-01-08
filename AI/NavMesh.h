#ifndef AI_NAVMESH
#define AI_NAVMESH
#include "Math\Math.h"

#include <vector>
namespace Rain {
	namespace AI {
		class Polygon {
		public:
			Polygon() {

			}
			Polygon(std::vector<Math::Vector2> i_vertices) {
				vertices.resize(i_vertices.size());
				swap(vertices, i_vertices);
				center = GetCenter();
				int q;
			}
			std::vector<Math::Vector2> vertices;
			Math::Vector2 center;
			void GenerateConvexPolygons(std::vector<Polygon>& convexPolygons) {
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

			Math::Vector2 GetCenter() {
				int count = vertices.size();
				Math::Vector2 center(0, 0);
				for (int i = 0; i < count; i++) {
					center = center + vertices[i] / count;
				}
				return center;
			}

			//helpers
			//-----------------------
			bool IsConcave(int i_index) {
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

			int FindDiagonal(int i_index) {
				int count = vertices.size();
				for (int i = 2; i < count - 1; i++) {
					if (IsInAngel(i_index, (i_index + i) % count) && !IsIntersected(i_index, (i_index + i) % count)) {
						return (i_index + i) % count;
					}
				}
				//Fail
				return -1;
			}

			void PartitionDiagonal(int i_index0, int i_index1, std::vector<Polygon>& convexPolygons) {
				int count = vertices.size();
				std::vector<Math::Vector2> verticesLeft;
				std::vector<Math::Vector2> verticesRight;
				if (i_index0 < i_index1) {
					for (int i = i_index0; i <= i_index1; i++) {
						verticesLeft.push_back(vertices[i]);
					}
					for (int i = i_index1; i <= i_index0+count; i++) {
						verticesRight.push_back(vertices[i%count]);
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
			bool IsInAngel(int i_index0, int i_index1) {
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

			bool IsIntersected(int i_index0, int i_index1) {

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

			bool IsIntersected(Math::Vector2 vtc0, Math::Vector2 vtc1, Math::Vector2 vtc2, Math::Vector2 vtc3) {
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
		};
		class NavMesh
		{
			struct Edge {
				float weight;
				Math::Vector2 vtc0;
				Math::Vector2 vtc1;
				Edge() {
					weight = 0;
				}
				Edge(Math::Vector2 i_vtc0, Math::Vector2 i_vtc1, float i_wei) {
					weight = i_wei;
					vtc0 = i_vtc0;
					vtc1 = i_vtc1;
				}
			};
		public:
			 Polygon polygonData;
			 std::vector<Polygon> convexPolygons;
			 std::vector<std::vector<Edge>> adjacencyTbl;

			 void GenerateNavMesh() {
				 polygonData.GenerateConvexPolygons(convexPolygons);
				 GenerateAdjacencyTable();
				 int r;
			 }
			 void GenerateAdjacencyTable() {
				 int count = convexPolygons.size();
				 for (int i = 0; i < count; i++) {
					 std::vector<Edge> edges;
					 for (int j = 0; j < count; j++) {
						 edges.push_back(Edge());
					 }
					 adjacencyTbl.push_back(edges);
				 }

				 for (int i = 0; i < count; i++) {
					 for (int j = i+1; j < count; j++) {
						 if (IsCollinear(convexPolygons[i], convexPolygons[j], adjacencyTbl[i][j])) {
							 adjacencyTbl[j][i].vtc0 = adjacencyTbl[i][j].vtc0;
							 adjacencyTbl[j][i].vtc1 = adjacencyTbl[i][j].vtc1;
							 adjacencyTbl[j][i].weight= adjacencyTbl[i][j].weight;
						 }
						 else {
							 adjacencyTbl[i][j].weight = -1;
							 adjacencyTbl[j][i].weight = -1;
						 }
					 }
				 }
			 }
			 bool IsCollinear(const Polygon& plg0, const Polygon& plg1, Edge& i_edge) {
				 int count0 = plg0.vertices.size();
				 int count1 = plg1.vertices.size();
				 for (int i = 0; i < count0; i++) {
					 for (int j = 0; j < count1; j++) {
						 if (plg0.vertices[(i + 1) % count0] == plg1.vertices[j] && plg0.vertices[i] == plg1.vertices[(j + 1) % count1]) {
							 i_edge.vtc0 = plg0.vertices[i];
							 i_edge.vtc1 = plg0.vertices[(i + 1) % count0];
							 i_edge.weight = Distance(i_edge.vtc0, i_edge.vtc1);
							 return true;
						 }
					 }
				 }
				 return false;
			 }

			 float Distance(Math::Vector2 i_vtc0, Math::Vector2 i_vtc1) {
				 float x = (i_vtc1 - i_vtc0).x;
				 float y = (i_vtc1 - i_vtc0).y;
				 return sqrtf(x * x + y * y);
			 }

			 float GetPath(Math::Vector2 i_vtc0, Math::Vector2 i_vtc1) {

			 }
		};
	}
}



#endif // !AI_NAVMESH

