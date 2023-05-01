#include "CameraComponent.h"
#include "CameraSystem.h"
void Rain::Camera::CameraComponent::Initialize() {

}
void Rain::Camera::CameraComponent::Update(double i_timeSinceLastFrame) {

}
void Rain::Camera::CameraComponent::Destroy() {

}
Rain::Camera::CameraComponent::CameraComponent() {
	id = -1;
	isMain = false;
	nearPlane = 0;
	farPlane = 0;
	horizental = 0;
	vertical = 0;
}

Rain::Camera::CameraComponent::CameraComponent(int i_id, std::shared_ptr <ECS::Entity> i_entity, bool i_isMain, float i_near, float i_far, float i_horz, float i_vert):ComponentBase(i_id,i_entity){

	isMain = i_isMain;
	if (isMain) {
		Camera::CameraSystem::GetInstance()->mainCamera = std::shared_ptr<CameraComponent>(this);
	}
	nearPlane = i_near;
	farPlane = i_far;
	horizental = i_horz;
	vertical = i_vert;
}

Rain::Camera::CameraComponent::~CameraComponent() {

}