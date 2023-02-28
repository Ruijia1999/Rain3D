#include "AnimationClip.h"
#include "AnimationImporter.h"
#include "Animation\KeyFrame.h"
#define SECOND_PER_FRAME 0.04

void Rain::Animation::AnimationClip::Initialize() {
	
}
bool Rain::Animation::AnimationClip::Update(bool loop, int& i_frame, double& i_time, double i_timeSinceLastFrame, Math::Vector3& velTranslate, Math::Vector3& velScale, Transform::TransformComponent* transform){
	i_time += i_timeSinceLastFrame;
	if (i_time >= pipelines[0].keyFrames[i_frame + 1].time*SECOND_PER_FRAME) {
		i_frame++;
		if (loop) {
			if (i_frame >= pipelines[0].frameCount - 1) {
				i_frame = 0;
				i_time = 0;
			}
		}else {
			if (i_frame >= pipelines[0].frameCount - 1) {
				float posX = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationX);
				float posY = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationY);
				float posZ = GetValue(loop, i_frame, i_time, AnimPipelineType::TranslationZ);
				transform->position = Math::Vector3(posX, posY, posZ);

				float scaleX = GetValue(loop, i_frame, i_time, AnimPipelineType::ScaleX);
				float scaleY = GetValue(loop, i_frame, i_time, AnimPipelineType::ScaleY);
				float scaleZ = GetValue(loop, i_frame, i_time, AnimPipelineType::ScaleZ);
				transform->scale = Math::Vector3(scaleX, scaleY, scaleZ);
				return false;
			}
		}
		
		UpdateTransform(loop, i_frame, i_time, velTranslate, velScale, transform);
	}
	else {
		transform->position = transform->position + velTranslate * i_timeSinceLastFrame;
		transform->scale = transform->scale + velScale * i_timeSinceLastFrame;
	}
	return true;
}
void Rain::Animation::AnimationClip::UpdateTransform(bool loop, int i_frame, double i_time, Math::Vector3& velTranslate, Math::Vector3& velScale, Transform::TransformComponent* transform) {
	float slopePosX = GetSlope(loop, i_frame,AnimPipelineType::TranslationX);
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
	velScale = Math::Vector3(slopeScaleX, slopeScaleY, slopeScaleZ);
}
float Rain::Animation::AnimationClip::GetValue(bool loop, int i_frame, double i_time, AnimPipelineType i_type) {

	int j = GetPipeline(i_type);

	float value = pipelines[j].keyFrames[i_frame].value;
	if (i_frame >= pipelines[j].frameCount - 1) {
		return value;
	}
	float slope = GetSlope(loop, i_frame, i_type);
	float rslt = value + slope * (i_time - pipelines[GetPipeline(i_type)].keyFrames[i_frame].time * SECOND_PER_FRAME);
	return rslt;
}
float Rain::Animation::AnimationClip::GetSlope(bool loop, int i_frame, AnimPipelineType i_type) {
	KeyFramePipeline& pipeline = pipelines[GetPipeline(i_type)];
	
	return (pipeline.keyFrames[i_frame + 1].value - pipeline.keyFrames[i_frame].value) / (pipeline.keyFrames[i_frame + 1].time - pipeline.keyFrames[i_frame].time) / SECOND_PER_FRAME;

}

int Rain::Animation::AnimationClip::GetPipeline(AnimPipelineType i_type) {
	switch (i_type) {
	case AnimPipelineType::TranslationX:
		return 0;
	case AnimPipelineType::TranslationY:
		return 1;
	case AnimPipelineType::TranslationZ:
		return 2;
	case AnimPipelineType::ScaleX:
		return 6;
	case AnimPipelineType::ScaleY:
		return 7;
	case AnimPipelineType::ScaleZ:
		return 8;

	}
}


