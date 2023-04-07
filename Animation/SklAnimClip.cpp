#include "SklAnimClip.h"
#include "AnimationImporter.h"
#include "Animation\KeyFrame.h"


void Rain::Animation::SklAnimClip::Initialize() {

}
float Rain::Animation::SklAnimClip::GetTransValue(bool loop, int i_frame, int i_jointIndex, AnimPipelineType i_type) {
	int j = GetPipeline(i_type);

	return jointsAnim[i_jointIndex].pipelines[j].keyFrames[i_frame].value;
}

Rain::Math::Quaternion Rain::Animation::SklAnimClip::GetRotateValue(bool loop, int i_frame, int i_time, int i_jointIndex) {
	Math::Quaternion rotateVal;

	
	float rotateX = GetTransValue(loop, i_frame, i_jointIndex, AnimPipelineType::RotationX);
	float rotateY = GetTransValue(loop, i_frame, i_jointIndex, AnimPipelineType::RotationY);
	float rotateZ = GetTransValue(loop, i_frame, i_jointIndex, AnimPipelineType::RotationZ);
	Math::Quaternion previous(rotateX, rotateY, rotateZ);
	//Math::Quaternion previous(Math::AngleToRadian(rotateX), Math::AngleToRadian(rotateY), Math::AngleToRadian(rotateZ));
	
	rotateX = GetTransValue(loop, i_frame+1, i_jointIndex, AnimPipelineType::RotationX);
	rotateY = GetTransValue(loop, i_frame+1, i_jointIndex, AnimPipelineType::RotationY);
	rotateZ = GetTransValue(loop, i_frame+1, i_jointIndex, AnimPipelineType::RotationZ);
	Math::Quaternion next(rotateX, rotateY, rotateZ);

//	Slerp(previous, next, i_time - jointsAnim[i_jointIndex].pipelines[GetPipeline(AnimPipelineType::RotationX)].keyFrames[i_frame].time * SECOND_PER_FRAME, rotateVal);
	return previous;
}
float Rain::Animation::SklAnimClip::GetValue(bool loop, int i_frame, double i_time, int i_jointIndex, AnimPipelineType i_type) {

	int j = GetPipeline(i_type);

	float value = jointsAnim[i_jointIndex].pipelines[j].keyFrames[i_frame].value;
	if (i_frame >= jointsAnim[i_jointIndex].pipelines[j].frameCount - 1) {
		return value;
	}
	float slope = GetSlope(loop, i_frame, i_jointIndex, i_type);
	float rslt = value + slope * (i_time - jointsAnim[i_jointIndex].pipelines[GetPipeline(i_type)].keyFrames[i_frame].time * SECOND_PER_FRAME);
	return rslt;
}
float Rain::Animation::SklAnimClip::GetSlope(bool loop, int i_frame, int i_jointIndex, AnimPipelineType i_type) {
	KeyFramePipeline& pipeline = jointsAnim[i_jointIndex].pipelines[GetPipeline(i_type)];

	return (pipeline.keyFrames[i_frame + 1].value - pipeline.keyFrames[i_frame].value) / (pipeline.keyFrames[i_frame + 1].time - pipeline.keyFrames[i_frame].time) / SECOND_PER_FRAME;

}

int Rain::Animation::SklAnimClip::GetPipeline(AnimPipelineType i_type) {
	switch (i_type) {
	case AnimPipelineType::TranslationX:
		return 0;
	case AnimPipelineType::TranslationY:
		return 1;
	case AnimPipelineType::TranslationZ:
		return 2;
	case AnimPipelineType::RotationX:
		return 3;
	case AnimPipelineType::RotationY:
		return 4;
	case AnimPipelineType::RotationZ:
		return 5;

	}
}


bool Rain::Animation::SklAnimClip::Update(bool loop, int& i_frame, double& i_time, double i_timeSinceLastFrame, Math::Vector3& i_velTranslate, Math::Quaternion& previousRotate, Math::Quaternion& nextRotate, MeshRender::MeshRenderComponent* i_sklMesh) {
	Animation::Pose* pose = new Animation::Pose(jointsAnim.size());
	
	i_time += i_timeSinceLastFrame;
	if (i_time >= jointsAnim[0].pipelines[0].keyFrames[i_frame + 1].time * SECOND_PER_FRAME) {
		i_frame++;
		if (loop) {
			if (i_frame >= jointsAnim[0].pipelines[0].frameCount - 1) {
				i_time -= jointsAnim[0].pipelines[0].keyFrames[i_frame].time * SECOND_PER_FRAME;
				i_frame = 0;
			}
		}
		else {
			if (i_frame >= jointsAnim[0].pipelines[0].frameCount - 1) {
				return false;
			}
		}
	}
	for (int i = 0; i < jointsAnim.size(); i++) {
		float posX = GetTransValue(loop, i_frame, i, AnimPipelineType::TranslationX);
		float posY = GetTransValue(loop, i_frame, i, AnimPipelineType::TranslationY);
		float posZ = GetTransValue(loop, i_frame, i, AnimPipelineType::TranslationZ);
		pose->transformation[i] = Math::Vector3(posX, posY, posZ);
		pose->rotation[i] = GetRotateValue(loop, i_frame, i_time, i);
	}
	i_sklMesh->skeletalMesh->UpdateMesh(pose);
	return true;
}

void Rain::Animation::SklAnimClip::Slerp(const Math::Quaternion& quaternion1, const Math::Quaternion& quaternion2, float i_time, Math::Quaternion& quaternion) {

}