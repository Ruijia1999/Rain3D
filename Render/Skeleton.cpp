#include "Skeleton.h"
#include "Transform\TransformSystem.h"
void Rain::Render::Skeleton::UpdateJointsPosition() {
	UpdateSingleJointPosition(rootJoint, nullptr);
}

void Rain::Render::Skeleton::UpdateSingleJointPosition(Joint* joint, Joint* parentJoint) {
	if (joint == nullptr) {
		return;
	}
	if (joint == rootJoint) {
		
		Math::Matrix m = Math::Matrix(Math::Vector3(joint->translation.x, joint->translation.y, joint->translation.z));
		Math::Matrix j = Math::Matrix(joint->rotate);
		Math::Matrix l = Math::Matrix(joint->jointOrient);
		Math::Matrix k;
		k.Invert();

		joint->transformMatrix = k * (l * (m * j));
		joint->transformMatrix.Invert();

		Math::Vector4 t(joint->translation, 1);
		joint->worldPosition = k*t;

	}
	else {
		Math::Matrix m =  Math::Matrix(Math::Vector3(joint->translation.x, joint->translation.y, joint->translation.z));
		Math::Matrix j = Math::Matrix(joint->rotate);
		Math::Matrix l = Math::Matrix(joint->jointOrient);
		l.Invert();
		Math::Matrix k = parentJoint->transformMatrix;
		k.Invert();

		joint->transformMatrix = (k * (m * (j*l)));
		joint->transformMatrix.Invert();
		if (joint->name == "MikeFreeman_RightUpLeg") {
			int a = 1;
		}
		Math::Vector4 t(joint->translation, 1);
		
		joint->worldPosition = parentJoint->transformMatrix *  t;
		
		int v = 1;
	}

	for (auto child : joint->children) {
		UpdateSingleJointPosition(jointArray[child], joint);
	}
}

Rain::Math::Vector3 Rain::Render::Skeleton::GetPositionByIndex(int i_index) {
	Math::Vector3 rslt(jointArray[i_index]->worldPosition[0], jointArray[i_index]->worldPosition[1], jointArray[i_index]->worldPosition[2]);
	return rslt;
}