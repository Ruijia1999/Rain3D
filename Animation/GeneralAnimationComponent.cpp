#include "GeneralAnimationComponent.h"
#include "Transform\TransformSystem.h"
#include "Time\Time.h"
Rain::Animation::GeneralAnimationComponent::GeneralAnimationComponent():AnimationComponent() {
	currentClip = nullptr;

}
Rain::Animation::GeneralAnimationComponent::GeneralAnimationComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity, std::shared_ptr<GeneralAnimationClip> i_clip, bool i_autoPlay, bool i_loop, bool i_relative) : AnimationComponent(i_id, i_entity,i_autoPlay,i_loop) {
	currentClip = i_clip;
	isRelative = i_relative;
	Initialize();
}
Rain::Animation::GeneralAnimationComponent::~GeneralAnimationComponent() {

}
void Rain::Animation::GeneralAnimationComponent::Initialize() {
	if (autoPlay) {
		currentTime = 0;
		currentFrame = -1;
		velScale = Math::Vector3(0, 0, 0);
		velTranslate = Math::Vector3(0, 0, 0);
		Play();
	}
	else {
		isPlaying = false;
		currentTime = 0;
		currentFrame = -1;
		velTranslate = Math::Vector3(0, 0, 0);
		velScale = Math::Vector3(0, 0, 0);
	}
}
void Rain::Animation::GeneralAnimationComponent::Update(double i_timeSinceLastFrame) {
	if (!isPlaying) {
		return;
	}
	double secondTime = Time::ConvertTicksToSeconds(i_timeSinceLastFrame);

	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	Math::Quaternion rotate;
	if (!currentClip->Update(loop, isRelative, currentFrame, currentTime, secondTime, animTranslate, transform)) {
		Stop();
	}
	else {
		if (isRelative) {
			transform->position = transform->position + animTranslate - prevAnimTranslate;
			prevAnimTranslate = animTranslate;
		}
	}
}
void Rain::Animation::GeneralAnimationComponent::Destroy() {

}
void Rain::Animation::GeneralAnimationComponent::Play() {
	if (isPlaying) {
		return;
	}
	isPlaying = true;
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	if (isRelative) {
		orgTranslate = transform->position;
		prevAnimTranslate = Math::Vector3(0, 0, 0);
	}


	
}
void Rain::Animation::GeneralAnimationComponent::Pause() {
	isPlaying = false;
}
void Rain::Animation::GeneralAnimationComponent::Stop() {
	isPlaying = false;
	currentTime = 0;
	currentFrame = -1;
	velTranslate = Math::Vector3(0, 0, 0);
	velScale = Math::Vector3(0, 0, 0);
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	if (isRelative) {
	
	}
	else {
		transform->position = orgTranslate;
	}

	
}
