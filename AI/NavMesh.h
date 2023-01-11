#ifndef AI_NAVMESH
#define AI_NAVMESH
#include "Math\Math.h"
#include <vector>
namespace Rain {
	namespace AI {
		class Polygon {
		public:
			Polygon();
			Polygon(std::vector<Math::Vector2> i_vertices);
			std::vector<Math::Vector2> vertices;
			Math::Vector2 center;
			void GenerateConvexPolygons(std::vector<Polygon>& convexPolygons);
			Math::Vector2 GetCenter();

			Polygon& operator=(const Polygon& i_polygon) {
				if (this != &i_polygon) {
					vertices = i_polygon.vertices;
				}
				return *this;
			}
			//helpers
			//-----------------------
			bool IsConcave(int i_index);

			int FindDiagonal(int i_index);

			void PartitionDiagonal(int i_index0, int i_index1, std::vector<Polygon>& convexPolygons);
			bool IsInAngel(int i_index0, int i_index1);

			bool IsIntersected(int i_index0, int i_index1);

			bool IsInPolygon(Math::Vector2 vtc);

			bool IsIntersected(Math::Vector2 vtc0, Math::Vector2 vtc1, Math::Vector2 vtc2, Math::Vector2 vtc3);
		};
		
		class NavMesh
		{

		public:
			NavMesh() {

			}
			Polygon polygonData;
			std::vector<Polygon> convexPolygons;

			 void GenerateNavMesh();
			 int GetPolygonIn(Math::Vector2 i_vtc);

		};
	}
}



#endif // !AI_NAVMESH

