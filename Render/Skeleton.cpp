#include "Skeleton.h"
#include "Transform\TransformSystem.h"
void Rain::Render::Skeleton::UpdateJointsPosition() {
	UpdateSingleJointPosition(rootJoint, nullptr);
}

void Rain::Render::Skeleton::UpdateSingleJointPosition(Joint* joint, const Joint* parentJoint) {
	if (joint == nullptr) {
		return;
	}
	if (joint == rootJoint) {
		Math::Matrix matrix = Math::CreateLocalToWorldTransform(joint->rotate, joint->translation, joint->scale);
		matrix.Inverse();
		joint->worldPosition = matrix* Math::Vector4(0,0,0,1);
		int j = 0;
	}
	else {
		Math::Matrix matrix = Math::CreateLocalToWorldTransform(joint->rotate, joint->translation, joint->scale);
		matrix.Inverse();
		joint->worldPosition = matrix * parentJoint->worldPosition;
		int j = 0;
	}

	for (auto child : joint->children) {
		UpdateSingleJointPosition(jointArray[child], joint);
	}
}
Rain::Math::Vector3 Rain::Render::Skeleton::GetPositionByIndex(int i_index) {
	Math::Vector3 rslt(jointArray[i_index]->worldPosition[0], jointArray[i_index]->worldPosition[1], jointArray[i_index]->worldPosition[2]);
	return rslt;
}