#include "World.h"
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"
#include "Render/Mesh.h"
#include "Render/Effect.h"
#include "Render/RenderData.h"
#include "Render/ConstantBuffer.h"
#include "Render/Graphics.h"

#include <vector>
namespace{
	std::vector<Rain::Render::RenderData> RenderData;
}
void Rain::ECS::World::Initialize() {
	GameObject::GameObjectSystem::GetInstance()->Initialize();
	Transform::TransformSystem::GetInstance()->Initialize();

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
	RenderData.push_back(Render::RenderData(s_mesh, s_effect, vsConstantBuffer));
	
}
void Rain::ECS::World::Update() {
	GameObject::GameObjectSystem::GetInstance()->Update();
	Transform::TransformSystem::GetInstance()->Update();
	SubmitRenderData();
}

void Rain::ECS::World::SubmitRenderData() {
	Render::Graphics::NextRenderData.swap(RenderData);
}