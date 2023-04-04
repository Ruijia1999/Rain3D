#include "SklAnimationComponent.h"
#include "Transform\TransformSystem.h"
#include "Time\Time.h"


Rain::Animation::SklAnimationComponent::SklAnimationComponent() {
	currentClip = nullptr;
	currentTime = 0;
	autoPlay = true;
	loop = false;
}

Rain::Animation::SklAnimationComponent::SklAnimationComponent(int i_id, std::shared_ptr<SklAnimClip> i_clip, bool i_autoPlay, bool i_loop) {
	id = i_id;
	currentClip = i_clip;
	autoPlay = i_autoPlay;
	loop = i_loop;
	Initialize();
}

Rain::Animation::SklAnimationComponent::~SklAnimationComponent() {

}
void Rain::Animation::SklAnimationComponent::Initialize() {
	if (autoPlay) {
		currentTime = 0;
		currentFrame = -1;

		Play();
	}
	else {
		isPlaying = false;
		currentTime = 0;
		currentFrame = -1;

	}
}
void Rain::Animation::SklAnimationComponent::Update(double i_timeSinceLastFrame) {
	if (!isPlaying) {
		return;
	}
	double secondTime = Time::ConvertTicksToSeconds(i_timeSinceLastFrame);
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	//Mesh
	//if (!currentClip->Update(loop, currentFrame, currentTime, secondTime, )) {
	//	Stop();
	//}
}
void Rain::Animation::SklAnimationComponent::Destroy() {

}
void Rain::Animation::SklAnimationComponent::Play() {
	if (isPlaying) {
		return;
	}
	isPlaying = true;
	Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);


}
void Rain::Animation::SklAnimationComponent::Pause() {
	isPlaying = false;
}
void Rain::Animation::SklAnimationComponent::Stop() {
	isPlaying = false;
	currentTime = 0;
	currentFrame = -1;

	//Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id);
	//transform->position = orgTranslate;
	//transform->scale = orgScale;

}
