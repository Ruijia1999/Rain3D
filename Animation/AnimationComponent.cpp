#include "AnimationComponent.h"
#include "Transform\TransformSystem.h"
#include "Time\Time.h"

Rain::Animation::AnimationComponent::AnimationComponent() {
	currentTime = 0;
	autoPlay = true;
	loop = false;
}

Rain::Animation::AnimationComponent::AnimationComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity, bool i_autoPlay, bool i_loop):ComponentBase(i_id, i_entity) {
	autoPlay = i_autoPlay;
	loop = i_loop;
}

Rain::Animation::AnimationComponent::~AnimationComponent() {

}