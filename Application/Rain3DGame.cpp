#include "Rain3DGame.h"
#include "ECS/World.h"
#include "Input/Input.h"
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"
#include "Render/RenderData.h"
#include "Render/Graphics.h"
#include "Time/Time.h"
#include "Asset/SceneLoader.h"
#include "EngineLog/EngineLog.h"
#include "MeshRender/MeshRender.h"
#include "Render/RenderSystem.h"
#include "Collision/ColliderSystem.h"

using namespace std::placeholders;
using namespace Rain;
namespace {
    std::vector<Rain::Render::RenderData> RenderData;
    std::vector<Rain::ECS::Entity*> entities;
    uint64_t timeLastFrame;
    bool stop;
    Math::Vector3 cameraPos;
    Math::Quaternion cameraRot;
    std::thread* mainGameThread;
}
void Rain::Rain3DGame::AddEntity(Rain::ECS::Entity* i_entity) {
    entities.push_back(i_entity);
}

Rain::ECS::Entity* Rain::Rain3DGame::GetEntity(int i_id) {
    for (auto entity : entities) {
        if (entity->id == i_id) {
            return entity;
        }
    }
    return nullptr;
}


void Rain::Rain3DGame::StartGame() {
    stop = false;
    while (!stop) {
        Update();
    }
    int exit = 1;
}
void Rain::Rain3DGame::InitializeSettings(Math::Vector3 ligthDirection, Math::Quaternion i_cameraRot, Math::Vector3 i_cameraPos) {
    cameraPos = i_cameraPos;
    cameraRot = i_cameraRot;
}
void Rain::Rain3DGame::Initialize(HWND hWnd, int width, int height) {
    
    Rain::EngineLog::CreateLogFile("log");

    Rain::Input::Initialize();
    Rain::Time::Initialize();
    Rain::Render::RenderSystem::Initialize(hWnd,width, height);

    GameObject::GameObjectSystem::GetInstance()->Initialize();
    Transform::TransformSystem::GetInstance()->Initialize();
    MeshRender::MeshRenderSystem::GetInstance()->Initialize();
    ColliderSystem::GetInstance()->Initialize();
    Rain::Asset::SceneLoader::RegisterComponentCreators();
    Rain::Asset::SceneLoader::LoadScene("test");

    timeLastFrame = 0;
    mainGameThread = new std::thread( StartGame);
}

void Rain::Rain3DGame::Update() {
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
    for (auto entity : entities) {
        if (entity != nullptr) {
            double i = Time::ConvertTicksToSeconds(timeSinceLastFrame);
            entity->Update(Time::ConvertTicksToSeconds(timeSinceLastFrame));
        }
    }
    Input::Update(Time::ConvertTicksToSeconds(timeSinceLastFrame));
    GameObject::GameObjectSystem::GetInstance()->Update(timeSinceLastFrame);
    Transform::TransformSystem::GetInstance()->Update(timeSinceLastFrame);
    ColliderSystem::GetInstance()->Update(timeSinceLastFrame);

    //Init Constant Buffer
    RenderData.clear();
    std::vector<GameObject::GameObjectComponent*> gameobjects = GameObject::GameObjectSystem::GetInstance()->GetAllComponents<GameObject::GameObjectComponent>();
    for (int i = 0; i < entities.size(); i++) {
        GameObject::GameObjectComponent* go = gameobjects[i];
        if (go->isActive) {

            Render::ConstantBuffer::VSConstantBuffer vsConstantBuffer;
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(go->id);
            vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(1, 200, 1.57079632, 1.02477892);
            vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(transform->rotation, transform->position);
            vsConstantBuffer.transform_localToWorld.Inverse();
            //vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(Math::Quaternion(-0.7068252, 0, 0, 0.7073883), Math::Vector3(0, 0, -100));
            vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(cameraRot, cameraPos);

            vsConstantBuffer.transform_worldToCamera.Inverse();
            
            MeshRender::MeshRenderComponent* meshRender = MeshRender::MeshRenderSystem::GetInstance()->GetComponent<MeshRender::MeshRenderComponent>(go->id);
            vsConstantBuffer.color = meshRender->color;
            RenderData.push_back(Render::RenderData(meshRender->mesh, meshRender->effect, vsConstantBuffer));

        }
    }
    Render::Graphics::NextRenderData.resize(RenderData.size());
    Render::Graphics::NextRenderData.swap(RenderData);
    Rain::Render::RenderSystem::Update();
}
void Rain::Rain3DGame::ExitGame() {
    stop = true;
}
void Rain::Rain3DGame::ClearUp() {
    int j = 0;
}
