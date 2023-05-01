#include "SklAnimClip.h"
#include "AnimationImporter.h"
#include "Animation\KeyFrame.h"


void Rain::Animation::SklAnimClip::Initialize() {

}
float Rain::Animation::SklAnimClip::GetValue(bool loop, int i_frame, int i_jointIndex, AnimPipelineType i_type) {
	int j = GetPipeline(i_type);

	return jointsAnim[i_jointIndex].pipelines[j].keyFrames[i_frame].value;
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
		for (int i = 0; i < jointsAnim.size(); i++) {
			float posX = GetValue(loop, i_frame, i, AnimPipelineType::TranslationX);
			float posY = GetValue(loop, i_frame, i, AnimPipelineType::TranslationY);
			float posZ = GetValue(loop, i_frame, i, AnimPipelineType::TranslationZ);
			pose->transformation[i] = Math::Vector3(posX, posY, posZ);
			float rotateX = GetValue(loop, i_frame, i, AnimPipelineType::RotationX);
			float rotateY = GetValue(loop, i_frame, i, AnimPipelineType::RotationY);
			float rotateZ = GetValue(loop, i_frame, i, AnimPipelineType::RotationZ);
			pose->rotation[i] = Math::Quaternion(rotateX, rotateY, rotateZ);
		}
		i_sklMesh->UpdateSkeletalMesh(pose);
	}

	return true;
}
