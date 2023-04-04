#include "AnimationComponent.h"
#include "Transform\TransformSystem.h"
#include "Time\Time.h"

Rain::Animation::AnimationComponent::AnimationComponent() {
	currentTime = 0;
	autoPlay = true;
	loop = false;
}

Rain::Animation::AnimationComponent::AnimationComponent(int i_id, bool i_autoPlay, bool i_loop) {
	id = i_id;
	autoPlay = i_autoPlay;
	loop = i_loop;
}

Rain::Animation::AnimationComponent::~AnimationComponent() {

}