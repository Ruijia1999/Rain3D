#include "CameraSystem.h"
#include "EngineLog\EngineLog.h"
Rain::Camera::CameraSystem* Rain::Camera::CameraSystem::instance;

Rain::Camera::CameraSystem* Rain::Camera::CameraSystem::GetInstance() {
	if (instance == nullptr) {
		instance = new CameraSystem();
		return instance;
	}
	else {
		return instance;
	}
}

Rain::Camera::CameraSystem::CameraSystem() {

}

void Rain::Camera::CameraSystem::Initialize() {
	EngineLog::Log("Camera System is initialized successfully.");
}

void Rain::Camera::CameraSystem::SetMainCamera(int i_id) {

}