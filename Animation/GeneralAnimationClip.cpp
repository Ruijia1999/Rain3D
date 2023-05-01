#include "GeneralAnimationClip.h"
#include "AnimationImporter.h"
#include "Animation\KeyFrame.h"


void Rain::Animation::GeneralAnimationClip::Initialize() {
	
}


float Rain::Animation::GeneralAnimationClip::GetValue(bool loop, int i_frame, AnimPipelineType i_type) {

	int j = GetPipeline(i_type);

	return pipelines[j].keyFrames[i_frame].value;
}

int Rain::Animation::GeneralAnimationClip::GetPipeline(AnimPipelineType i_type) {
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
	case AnimPipelineType::ScaleX:
		return 6;
	case AnimPipelineType::ScaleY:
		return 7;
	case AnimPipelineType::ScaleZ:
		return 8;


	}
}


bool Rain::Animation::GeneralAnimationClip::Update(bool loop, bool isRelative, int& i_frame, double& i_time, double i_timeSinceLastFrame,  Math::Vector3& animPos, Transform::TransformComponent* transform) {
	i_time += i_timeSinceLastFrame;
	if (i_time >= pipelines[0].keyFrames[i_frame + 1].time * SECOND_PER_FRAME) {
		i_frame++;
		if (loop) {
			if (i_frame >= pipelines[0].frameCount - 1) {
				i_time -= pipelines[0].keyFrames[i_frame].time * SECOND_PER_FRAME;
				i_frame = 0;
				
			}
		}
		else {
			if (i_frame >= pipelines[0].frameCount - 1) {
				
				float posX = GetValue(loop, i_frame, AnimPipelineType::TranslationX);
				float posY = GetValue(loop, i_frame, AnimPipelineType::TranslationY);
				float posZ = GetValue(loop, i_frame, AnimPipelineType::TranslationZ);
		

				float scaleX = GetValue(loop, i_frame, AnimPipelineType::ScaleX);
				float scaleY = GetValue(loop, i_frame, AnimPipelineType::ScaleY);
				float scaleZ = GetValue(loop, i_frame, AnimPipelineType::ScaleZ);
	

				float rotateX = GetValue(loop, i_frame, AnimPipelineType::RotationX);
				float rotateY = GetValue(loop, i_frame, AnimPipelineType::RotationY);
				float rotateZ = GetValue(loop, i_frame, AnimPipelineType::RotationZ);
				
				if (isRelative) {
					animPos = Math::Vector3(posX, posY, posZ);
					transform->scale = Math::Vector3(scaleX, scaleY, scaleZ);
					transform->rotation = Math::Quaternion(rotateX, rotateY, rotateZ);
				}
				else {
					transform->position = Math::Vector3(posX, posY, posZ);
					transform->scale = Math::Vector3(scaleX, scaleY, scaleZ);
					transform->rotation = Math::Quaternion(rotateX, rotateY, rotateZ);
				}
				return false;
			}
		}

		float posX = GetValue(loop, i_frame, AnimPipelineType::TranslationX);
		float posY = GetValue(loop, i_frame, AnimPipelineType::TranslationY);
		float posZ = GetValue(loop, i_frame, AnimPipelineType::TranslationZ);


		float scaleX = GetValue(loop, i_frame, AnimPipelineType::ScaleX);
		float scaleY = GetValue(loop, i_frame, AnimPipelineType::ScaleY);
		float scaleZ = GetValue(loop, i_frame, AnimPipelineType::ScaleZ);


		float rotateX = GetValue(loop, i_frame, AnimPipelineType::RotationX);
		float rotateY = GetValue(loop, i_frame, AnimPipelineType::RotationY);
		float rotateZ = GetValue(loop, i_frame, AnimPipelineType::RotationZ);

		if (isRelative) {
			animPos = Math::Vector3(posX, posY, posZ);
			transform->scale = Math::Vector3(scaleX, scaleY, scaleZ);
			transform->rotation = Math::Quaternion(rotateX, rotateY, rotateZ);
		}
		else {
			transform->position = Math::Vector3(posX, posY, posZ);
			transform->scale = Math::Vector3(scaleX, scaleY, scaleZ);
			transform->rotation = Math::Quaternion(rotateX, rotateY, rotateZ);
		}
		
	}

	return true;
}

