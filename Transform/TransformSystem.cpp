#include "TransformSystem.h"
Rain::Transform::TransformSystem* Rain::Transform::TransformSystem::instance;

Rain::Transform::TransformSystem* Rain::Transform::TransformSystem::GetInstance() {
	if (instance == nullptr) {
		instance = new TransformSystem();
		return instance;
	}
	else {
		return instance;
	}
}

Rain::Transform::TransformSystem::TransformSystem(){

}