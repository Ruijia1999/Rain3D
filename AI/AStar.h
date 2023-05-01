#ifndef RAIN_AI_ASTAR
#define RAIN_AI_ASTAR
#include "NavMesh.h"
#include "Math/Vector2.h"
#include "Map.h"
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <list>
namespace Rain {
	namespace AI {
		struct PathNode {
			int index;
			PathNode* parent;
			float distance;
			//std::vector<PathNode> children;
			PathNode(int i_index, PathNode* i_parent) {
				index = i_index;
				parent = i_parent;
				distance = FLT_MAX;
			}

			PathNode(int i_index, PathNode* i_parent, float i_distance) {
				index = i_index;
				parent = i_parent;
				distance = i_distance;
			}
		};
		class AStar {
		public:
			Map* map;
			Math::Vector2 start;
			Math::Vector2 end;
			int startIndex;
			int endIndex;
			PathNode* curNode;
			int curIndex;


			AStar() {

			}
			AStar(Map* i_map) {
				map = i_map;
			}
			std::unordered_map<int,PathNode*> openList;
			std::unordered_map<int, PathNode*> closeList;
			void GetPath(Math::Vector2 i_start, Math::Vector2 i_end, std::list <Math::Vector2>& path);

			//Helper
			//------------------
			int TurnPoint(Math::Vector2 curVecLeft, Math::Vector2 curVecRight, Math::Vector2 nextVecLeft, Math::Vector2 nextVecRight);
			void ReorderVector(Math::Vector2& vtcLeft, Math::Vector2& vtcRight, Math::Vector2 viewPoint);
			PathNode* NextNode();
			float GetF(int curIndex, int nextIndex);
			float GetH(int nextIndex);

		};
	}


}
#endif // !RAIN_AI_ASTAR
