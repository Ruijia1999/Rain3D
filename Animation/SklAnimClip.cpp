#include "SklAnimClip.h"
#include "AnimationImporter.h"
#include "Animation\KeyFrame.h"


void Rain::Animation::SklAnimClip::Initialize() {

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


bool Rain::Animation::SklAnimClip::Update(bool loop, int& i_frame, double& i_time, double i_timeSinceLastFrame, MeshRender::MeshRenderComponent* i_sklMesh) {
	i_time += i_timeSinceLastFrame;
	for (int i = 0; i < jointsAnim.size(); i++) {
		//Set the mesh according to the keyframe data
		if (i_time >= jointsAnim[i].pipelines[0].keyFrames[i_frame + 1].time * SECOND_PER_FRAME) {
			i_frame++;
			if (loop) {
				if (i_frame >= jointsAnim[i].pipelines[0].frameCount - 1) {
					i_frame = 0;
					i_time = 0;
				}
			}
			else {
				if (i_frame >= jointsAnim[i].pipelines[0].frameCount - 1) {
	/*				float posX = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationX);
					float posY = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationY);
					float posZ = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationZ);*/
					
					Math::Quaternion rotation;

					return false;
				}
			}
		}
		//calculate the interpolation and update the mesh
		else {
		/*	transform->position = transform->position + velTranslate * i_timeSinceLastFrame;
			transform->scale = transform->scale + velScale * i_timeSinceLastFrame;*/
		}
	}
	
	return true;
}


void Rain::Animation::SklAnimClip::UpdateMesh(bool loop, int i_frame, double i_time, Math::Vector3& velTranslate, Math::Quaternion& velRotate, Math::Vector3& velScale, Transform::TransformComponent* transform) {
	/*float slopePosX = GetSlope(loop, i_frame, AnimPipelineType::TranslationX);
	float slopePosY = GetSlope(loop, i_frame, AnimPipelineType::TranslationY);
	float slopePosZ = GetSlope(loop, i_frame, AnimPipelineType::TranslationZ);
	float posX = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationX);
	float posY = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationY);
	float posZ = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationZ);
	transform->position = Math::Vector3(posX, posY, posZ);
	velTranslate = Math::Vector3(slopePosX, slopePosY, slopePosZ);
	float slopeScaleX = GetSlope(loop, i_frame, AnimPipelineType::ScaleX);
	float slopeScaleY = GetSlope(loop, i_frame, AnimPipelineType::ScaleY);
	float slopeScaleZ = GetSlope(loop, i_frame, AnimPipelineType::ScaleZ);
	float scaleX = GetValue(loop, i_frame, i_time, AnimPipelineType::ScaleX);
	float scaleY = GetValue(loop, i_frame, i_time, AnimPipelineType::ScaleY);
	float scaleZ = GetValue(loop, i_frame, i_time, AnimPipelineType::ScaleZ);
	transform->scale = Math::Vector3(scaleX, scaleY, scaleZ);
	velScale = Math::Vector3(slopeScaleX, slopeScaleY, slopeScaleZ);*/
}