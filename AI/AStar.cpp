#include "AStar.h"
void Rain::AI::AStar::GetPath(Math::Vector2 i_start, Math::Vector2 i_end, std::list <Math::Vector2>& path) {
	openList.clear();
	closeList.clear();
	startIndex = map->navMesh->GetPolygonIn(i_start);
	endIndex = map->navMesh->GetPolygonIn(i_end);

	int number = map->pointList.size();
	for (int i = 0; i < number; i++) {
		openList.insert(std::pair<int, PathNode*>(i, new PathNode(i, nullptr)));

	}
	curNode = openList.find(startIndex)->second;
	curNode->distance = 0;
	curIndex = startIndex;
	closeList.insert(std::pair<int, PathNode*>(startIndex, openList.find(startIndex)->second));
	openList.erase(startIndex);

	PathNode* aim = NextNode();

	std::stack<Math::Vector2> temp;

	/*while (aim->parent != nullptr) {
		temp.push(map->adjacencyTbl[aim->index][aim->parent->index].center);
		aim = aim->parent;
	}
	path.push_back(i_start);
	while (!temp.empty()) {
		path.push_back(temp.top());
		temp.pop();
	}
	path.push_back(i_end);*/

#pragma region  Turning Point Optimization

	Math::Vector2 curEdgeLeft;
	Math::Vector2 curEdgeRight;
	Math::Vector2 nextEdgeLeft;
	Math::Vector2 nextEdgeRight;
	Math::Vector2 viewPoint;

	Math::Vector2 curVecLeft;
	Math::Vector2 curVecRight;
	Math::Vector2 nextVecLeft;
	Math::Vector2 nextVecRight;

	viewPoint = i_end;
	if (aim->parent == nullptr) {
		path.push_back(i_start);
		path.push_back(i_end);
	}
	else {
		temp.push(i_end);
		curEdgeLeft = map->adjacencyTbl[aim->index][aim->parent->index].vtc1;
		curEdgeRight = map->adjacencyTbl[aim->index][aim->parent->index].vtc2;
		ReorderVector(curEdgeLeft, curEdgeRight, viewPoint);
		curVecLeft = curEdgeLeft - viewPoint;
		curVecRight = curEdgeRight - viewPoint;
		aim = aim->parent;
		while (aim->parent != nullptr) {
			nextEdgeLeft = map->adjacencyTbl[aim->index][aim->parent->index].vtc1;
			nextEdgeRight = map->adjacencyTbl[aim->index][aim->parent->index].vtc2;

			ReorderVector(nextEdgeLeft, nextEdgeRight, viewPoint);
			nextVecLeft = nextEdgeLeft - viewPoint;
			nextVecRight = nextEdgeRight - viewPoint;
			//Calculate
			switch (TurnPoint(curVecLeft, curVecRight, nextVecLeft, nextVecRight))
			{
			case 0:
				curEdgeLeft = nextEdgeLeft;
				curEdgeRight = nextEdgeRight;
				curVecLeft = curEdgeLeft - viewPoint;
				curVecRight = curEdgeRight - viewPoint;
				break;
			case 1:
				curEdgeRight = nextEdgeRight;
				curVecRight = curEdgeRight - viewPoint;
				break;
			case 2:
				curEdgeLeft = nextEdgeLeft;
				curVecLeft = curEdgeLeft - viewPoint;
				break;
			case 3:

				viewPoint = curEdgeLeft;
				curEdgeLeft = nextEdgeLeft;
				curEdgeRight = nextEdgeRight;
				curVecLeft = curEdgeLeft - viewPoint;
				curVecRight = curEdgeRight - viewPoint;
				temp.push(viewPoint);
				break;
			case 4:
				temp.push(viewPoint);
				viewPoint = curEdgeRight;
				curEdgeLeft = nextEdgeLeft;
				curEdgeRight = nextEdgeRight;
				curVecLeft = curEdgeLeft - viewPoint;
				curVecRight = curEdgeRight - viewPoint;
				temp.push(viewPoint);
				break;
			}
			aim = aim->parent;
		}

		Math::Vector2 lastVec = i_start - viewPoint;
		if (Math::IsLeft(lastVec, curVecLeft)) {
			temp.push(curEdgeLeft);
			temp.push(i_start);
		}
		else if (Math::IsLeft(lastVec, curVecRight)) {
			temp.push(i_start);
		}
		else if (Math::IsLeft(curVecRight, lastVec)) {
			temp.push(curEdgeRight);
			temp.push(i_start);
		}

		while (!temp.empty()) {
			path.push_back(temp.top());
			temp.pop();
		}
	}

#pragma endregion

	return;
}

//Helper
//------------------
int  Rain::AI::AStar::TurnPoint(Math::Vector2 curVecLeft, Math::Vector2 curVecRight, Math::Vector2 nextVecLeft, Math::Vector2 nextVecRight) {
	bool left = Math::IsLeft(curVecLeft, nextVecLeft);
	bool right = Math::IsLeft(nextVecRight, curVecRight);
	bool left1 = Math::IsLeft(nextVecRight, curVecLeft);
	bool right1 = Math::IsLeft(curVecRight, nextVecLeft);

	if (left && right) return 0;
	if ((!left) && right) return 1;
	if (left && (!right)) return 2;
	if (left1) return 3;
	if (right1) return 4;

}
void  Rain::AI::AStar::ReorderVector(Math::Vector2& vtcLeft, Math::Vector2& vtcRight, Math::Vector2 viewPoint) {
	Math::Vector2 vec1 = vtcLeft - viewPoint;
	Math::Vector2 vec2 = vtcRight - viewPoint;
	if ((vec1 ^ vec2) > 0) {
		Math::Vector2 temp = vtcLeft;
		vtcLeft = vtcRight;
		vtcRight = temp;
	}
}
Rain::AI::PathNode* Rain::AI::AStar::NextNode() {
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
	if (openList.empty()) {
		return nullptr;
	}
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
float  Rain::AI::AStar::GetF(int curIndex, int nextIndex) {
	return map->adjacencyTbl[curIndex][nextIndex].weight;
}
float  Rain::AI::AStar::GetH(int nextIndex) {
	return Distance(map->pointList[nextIndex], end);
}