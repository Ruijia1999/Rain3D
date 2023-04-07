#include "Skeleton.h"
#include "Transform\TransformSystem.h"
void Rain::Render::Skeleton::UpdateJointsPosition() {
	UpdateSingleJointPosition(rootJoint, nullptr,0, -1);
}

void Rain::Render::Skeleton::UpdateSingleJointPosition(Joint* joint, Joint* parentJoint, int index, int parentIndex) {
	if (joint == nullptr) {
		return;
	}
	if (joint == rootJoint) {
		
		Math::Matrix m = Math::Matrix(Math::Vector3(bindPose->transformation[index].x, bindPose->transformation[index].y, bindPose->transformation[index].z));
		Math::Matrix j = Math::Matrix(bindPose->rotation[index]);
		Math::Matrix l = Math::Matrix(joint->jointOrient);
		Math::Matrix k;
		k.Invert();

		bindPose->transformMatrix[index] = k * (l * (m * j));
		bindPose->transformMatrix[index].Invert();


	

	}
	else {
		Math::Matrix m = Math::Matrix(Math::Vector3(bindPose->transformation[index].x, bindPose->transformation[index].y, bindPose->transformation[index].z));
		Math::Matrix j = Math::Matrix(bindPose->rotation[index]);
		Math::Matrix l = Math::Matrix(joint->jointOrient);
		l.Invert();
		Math::Matrix k = bindPose->transformMatrix[parentIndex];
		k.Invert();

		bindPose->transformMatrix[index] = (k * (m * (j*l)));
		bindPose->transformMatrix[index].Invert();

		int v = 1;
	}

	for (auto child : joint->children) {
		UpdateSingleJointPosition(jointArray[child], joint, child, index);
	}
}

Rain::Math::Vector3 Rain::Render::Skeleton::GetPositionByIndex(int i_index) {
	Math::Vector3 rslt;
	return rslt;
}