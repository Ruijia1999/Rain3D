#include "AnimationComponent.h"
#include "Transform\TransformSystem.h"
#include "Time\Time.h"
Rain::Animation::AnimationComponent::AnimationComponent() {
	currentClip = nullptr;
	currentTime = 0;
	autoPlay = true;
	loop = false;
}
Rain::Animation::AnimationComponent::AnimationComponent(int i_id, std::shared_ptr<AnimationClip> i_clip, bool i_autoPlay, bool i_loop) {
	id = i_id;
	currentClip = i_clip;
	autoPlay = i_autoPlay;
	loop = i_loop;
	Initialize();
}
Rain::Animation::AnimationComponent::~AnimationComponent() {

}
void Rain::Animation::AnimationComponent::Initialize() {
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
void Rain::Animation::AnimationComponent::Update(double i_timeSinceLastFrame) {
	if (!isPlaying) {
		return;
	}
	double secondTime = Time::ConvertTicksToSeconds(i_timeSinceLastFrame);
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	if (!currentClip->Update(loop, currentFrame, currentTime, secondTime, velTranslate, velScale, transform)) {
		Stop();
	}
}
void Rain::Animation::AnimationComponent::Destroy() {

}
void Rain::Animation::AnimationComponent::Play() {
	if (isPlaying) {
		return;
	}
	isPlaying = true;
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	orgTranslate = transform->position;
	orgScale = transform->scale;
	
}
void Rain::Animation::AnimationComponent::Pause() {
	isPlaying = false;
}
void Rain::Animation::AnimationComponent::Stop() {
	isPlaying = false;
	currentTime = 0;
	currentFrame = -1;
	velTranslate = Math::Vector3(0, 0, 0);
	velScale = Math::Vector3(0, 0, 0);
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	transform->position = orgTranslate;
	transform->scale = orgScale;
	
}
