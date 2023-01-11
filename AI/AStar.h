#ifndef RAIN_AI_ASTAR
#define RAIN_AI_ASTAR
#include "NavMesh.h"
#include "Math/Vector2.h"
#include "Map.h"
#include <unordered_map>
#include <algorithm>
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
			void GetPath(Math::Vector2 i_start, Math::Vector2 i_end, OUT std::vector <Math::Vector2>& path ) {
				//startIndex = map->GetStartIndex(i_start);
				//endIndex = map->GetEndIndex(i_end);
				
				int number = map->pointList.size();
				for (int i = 0; i < number; i++) {
						openList.insert(std::pair<int, PathNode*>(i,new PathNode(i, nullptr)));
					
				}
				curNode = openList.find(startIndex)->second;
				curNode->distance = 0;
				curIndex = startIndex;
				closeList.insert(std::pair<int, PathNode*>(startIndex,openList.find(startIndex)->second));
				openList.erase(startIndex);

				PathNode* aim = NextNode();
			}

			//Helper
			//------------------

			PathNode* NextNode() {
				if (curIndex == endIndex) {
					return curNode;
				}
				//Update the adjacent nodes
				int number = map->pointList.size();
				for (int i = 0; i < number; i++) {
					if (map->adjacencyTbl[curIndex][i].weight != -1) {
						if (openList.find(i) != openList.end()) {
							if (openList.find(i)->second->distance > curNode->distance + GetF(curIndex, i) + GetH(i)) {
								openList.find(i)->second->distance = curNode->distance + GetF(curIndex, i) + GetH(i);
								openList.find(i)->second->parent = curNode;
							}
						}
					}
				}

				//Find the nearst node

				float min_distance = openList.begin()->second->distance;
				int min_index = openList.begin()->second->index;
				for (auto node : openList) {
					if (min_distance > node.second->distance) {
						min_distance = GetF(curIndex, node.first) + GetH(node.first);
						min_index = node.first;
					}
				}
				curNode = openList.find(min_index)->second;
				curIndex = min_index;
				closeList.insert(std::pair<int, PathNode*>(min_index, openList.find(min_index)->second));
				openList.erase(min_index);

				return NextNode();
			}
			float GetF(int curIndex,int nextIndex) {
				return map->adjacencyTbl[curIndex][nextIndex].weight;
			}
			float GetH(int nextIndex) {
				return Distance(map->pointList[nextIndex], end);
			}

		};
	}
}
#endif // !RAIN_AI_ASTAR
