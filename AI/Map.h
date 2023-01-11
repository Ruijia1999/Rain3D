#ifndef AI_MAP
#define AI_MAP
#include "Math\Math.h"
#include "NavMesh.h"
#include <vector>
namespace Rain {
	namespace AI {
		struct Edge {
			float weight;
			Math::Vector2 center;
			Edge();
		};

		class Map
		{
		public:
			NavMesh* navMesh;
			std::vector<Math::Vector2> pointList;
			std::vector<std::vector<Edge>> adjacencyTbl;

			void GenerateMap() {
				std::vector<Polygon> convexPolygons = navMesh->convexPolygons;

				int count = convexPolygons.size();
				for (int i = 0; i < count; i++) {
					std::vector<Edge> edges;
					for (int j = 0; j < count; j++) {
						edges.push_back(Edge());
					}
					adjacencyTbl.push_back(edges);
					pointList.push_back(convexPolygons[i].GetCenter());
				}
				//Adjacency Table
				for (int i = 0; i < count; i++) {
					for (int j = i + 1; j < count; j++) {
						GetCollinear(i, j);
					}
				}
				return;
			}

			bool GetCollinear(int index1, int index2) {
				std::vector<Polygon> convexPolygons = navMesh->convexPolygons;
				Polygon plg0 = convexPolygons[index1];
				Polygon plg1 = convexPolygons[index2];
				int count0 = plg0.vertices.size();
				int count1 = plg1.vertices.size();
				for (int i = 0; i < count0; i++) {
					for (int j = 0; j < count1; j++) {
						if (plg0.vertices[(i + 1) % count0] == plg1.vertices[j] && plg0.vertices[i] == plg1.vertices[(j + 1) % count1]) {
							adjacencyTbl[index1][index2].center = (plg0.vertices[(i + 1) % count0] + plg0.vertices[i])/2.0f;
							adjacencyTbl[index2][index1].center = adjacencyTbl[index1][index2].center;
							
							adjacencyTbl[index1][index2].weight = Distance(plg0.center, adjacencyTbl[index1][index2].center) + Distance(plg1.center, adjacencyTbl[index1][index2].center);
							adjacencyTbl[index2][index1].weight = adjacencyTbl[index1][index2].weight;
							return true;
						}
					}
				}
				return false;

			}

		};
	}
}



#endif // !AI_NAVMESH

