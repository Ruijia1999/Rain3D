#include "World.h"
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"
#include "Render/Mesh.h"
#include "Render/Effect.h"
#include "Render/RenderData.h"
#include "Render/ConstantBuffer.h"
#include "Render/Graphics.h"
#include "Time/Time.h"

#include <vector>
#include <cstdint>

namespace{
	std::vector<Rain::Render::RenderData> RenderData;
	uint64_t timeLastFrame;
}
Rain::ECS::World* Rain::ECS::World::Instance;
Rain::ECS::World* Rain::ECS::World::GetInstance() {
	if (Instance == nullptr) {
		Instance = new World();
		return Instance;
	}
	else {
		return Instance;
	}
}

void Rain::ECS::World::Initialize() {
	timeLastFrame = 0;
	GameObject::GameObjectSystem::GetInstance()->Initialize();
	Transform::TransformSystem::GetInstance()->Initialize();
}
void Rain::ECS::World::Update() {
	uint64_t timeSinceLastFrame;
	if (timeLastFrame == 0) {
		timeSinceLastFrame = 60;
		timeLastFrame = Time::GetCurrentSystemTimeTickCount();
	}
	else {
		uint64_t timeThisFrame = Time::GetCurrentSystemTimeTickCount();
		timeSinceLastFrame = timeThisFrame - timeLastFrame;
		timeLastFrame = timeThisFrame;
	}
	GameObject::GameObjectSystem::GetInstance()->Update(timeSinceLastFrame);
	Transform::TransformSystem::GetInstance()->Update(timeSinceLastFrame);

	//Graphics Portion
	Render::Mesh* s_mesh = new Render::Mesh();
	Render::Effect* s_effect = new Render::Effect();
	s_mesh->Initialize();
	s_effect->Initialize("vertexShader", "pixelShader");

	//Init Constant Buffer

	Render::ConstantBuffer::VSConstantBuffer vsConstantBuffer;
	vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(1.5708f, 1, 1, 10);
	vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(Math::Quaternion(), Math::Vector3(4, 0, 5));
	vsConstantBuffer.transform_localToWorld.Inverse();
	vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(Math::Quaternion(), Math::Vector3(0, 0, 10));
	vsConstantBuffer.transform_worldToCamera.Inverse();
	RenderData.clear();
	RenderData.push_back(Render::RenderData(s_mesh, s_effect, vsConstantBuffer));
	SubmitRenderData();
}

void Rain::ECS::World::SubmitRenderData() {
	Render::Graphics::NextRenderData.resize(RenderData.size());
	Render::Graphics::NextRenderData.swap(RenderData);
}

//helper----------------------------
void Rain::ECS::World::InitializeGameScene() {
	GameObject::GameObjectSystem::GetInstance()->AddComponent(0);

}