#include "Rain3DGame.h"
#include "ECS/World.h"
#include "Input/Input.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <corecrt_math_defines.h>
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
#include "Multithreading\Semaphore.h"
#include "Render\ConstantBufferFormats.h"
#include "Animation\AnimationSystem.h"
#include "Render\RenderDataBase.h"
#include "Render\SkeletonRenderData.h"
#include "Camera\Camera.h"
using namespace std::placeholders;
using namespace Rain;
namespace {
    std::vector<Rain::Render::RenderDataBase*> renderData;
    std::vector<std::shared_ptr<Rain::ECS::Entity>> entities;
    uint64_t timeLastFrame;
    uint64_t timeStart;
    bool stop;
    Math::Vector4 lightColor;
    Math::Vector3 lightDir;
    Math::Vector4 backgroundColor;

    std::thread* mainGameThread;
    std::thread* renderThread;
}
void Rain::Rain3DGame::AddEntity(std::shared_ptr<ECS::Entity> i_entity) {
    entities.push_back(i_entity);
}

std::shared_ptr<ECS::Entity> Rain::Rain3DGame::GetEntity(int i_id) {
    for (auto entity : entities) {
        if (entity->id == i_id) {
            return entity;
        }
    }
    return nullptr;
}


void Rain::Rain3DGame::StartGameThread() {
    timeStart = Time::GetCurrentSystemTimeTickCount();
    while (!stop) {
        Update();
    }
    ClearUp();
    int exit = 1;
}

void Rain::Rain3DGame::StartRenderThread() {
    Semaphore::Signal(NEW_RENDERDATA_PREPARED);
    while (!stop) {
        Sleep(16.667);
        Rain::Render::RenderSystem::Update();
    }
    Render::RenderSystem::CleanUp();

}
void Rain::Rain3DGame::InitializeSettings(Math::Vector4 i_lightColor, Math::Vector3 i_ligthDirection, Math::Vector4 i_backgroundColor) {

    lightColor = i_lightColor;
    i_ligthDirection.Normalize();
    lightDir = i_ligthDirection;
    backgroundColor = i_backgroundColor;

}
void Rain::Rain3DGame::Initialize(HWND hWnd, int width, int height) {

    Rain::EngineLog::CreateLogFile();
    Rain::Semaphore::Initialize();
    Rain::Input::Initialize();
    Rain::Time::Initialize();
    Rain::Render::RenderSystem::Initialize(hWnd, width, height);


    GameObject::GameObjectSystem::GetInstance()->Initialize();
    Camera::CameraSystem::GetInstance()->Initialize();
    Transform::TransformSystem::GetInstance()->Initialize();
    MeshRender::MeshRenderSystem::GetInstance()->Initialize();
    Animation::AnimationSystem::GetInstance()->Initialize();
    ColliderSystem::GetInstance()->Initialize();


    Rain::Asset::SceneLoader::RegisterComponentCreators();
    Rain::Asset::SceneLoader::LoadScene("test");
    Rain::Render::RenderSystem::SetBackground(backgroundColor);

    for (auto entity : entities) {
        entity->Initialize();
    }
    timeLastFrame = 0;

    stop = false;
    mainGameThread = new std::thread( StartGameThread);
    renderThread = new std::thread(StartRenderThread);
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
    Animation::AnimationSystem::GetInstance()->Update(timeSinceLastFrame);
    ColliderSystem::GetInstance()->Update(timeSinceLastFrame);

    std::shared_ptr<Camera::CameraComponent> mainCamera = Camera::CameraSystem::GetInstance()->mainCamera;
    Transform::TransformComponent* cameraTrans = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(mainCamera->id);
    //Init Constant Buffer
    renderData.clear();
    std::vector<GameObject::GameObjectComponent*> gameobjects = GameObject::GameObjectSystem::GetInstance()->GetAllComponents<GameObject::GameObjectComponent>();
    for (auto go: gameobjects) {
   
        if (go->isActive&&go->isVisible) {

            Render::ConstantBufferFormats::VSConstantBuffer vsConstantBuffer;
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(go->id);
            vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(mainCamera->nearPlane, mainCamera->farPlane, mainCamera->horizental*M_PI/180.0, mainCamera->vertical * M_PI / 180.0);
            vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(transform->rotation, transform->position, transform->scale);
            vsConstantBuffer.transform_localToWorld.Invert();
            vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(cameraTrans->rotation, cameraTrans->position);
            vsConstantBuffer.transform_worldToCamera.Invert();

            MeshRender::MeshRenderComponent* meshRender = MeshRender::MeshRenderSystem::GetInstance()->GetComponent<MeshRender::MeshRenderComponent>(go->id);
            vsConstantBuffer.color = meshRender->color;
            
            Render::ConstantBufferFormats::FrameConstantBuffer frameConstantBuffer;
            frameConstantBuffer.time = Time::ConvertTicksToSeconds(Time::GetCurrentSystemTimeTickCount() - timeStart);
            Math::Vector4 cameraForward = Math::Matrix(cameraTrans->rotation) * Math::Vector4(0, 0, 1,1);
            frameConstantBuffer.cameraForward = Math::Vector3(cameraForward.x, cameraForward.y, cameraForward.z);
            frameConstantBuffer.cameraPos = cameraTrans->position;
            frameConstantBuffer.lightColor = lightColor;
            frameConstantBuffer.lightDirection = lightDir;
            if (meshRender->meshType == 0) {
                renderData.push_back(new Render::RenderData(meshRender->mesh, meshRender->effect, meshRender->texture, meshRender->normalMap, vsConstantBuffer, frameConstantBuffer));
            }
            else if (meshRender->meshType == 1) {
                renderData.push_back(new Render::SkeletonRenderData(meshRender->skeletalMesh, meshRender->pose, meshRender->effect, meshRender->texture, meshRender->normalMap, vsConstantBuffer, frameConstantBuffer));
            }
            

        }
    }
    Semaphore::Wait(DATA_RENDER_COMPLETED);
    Render::Graphics::NextRenderData.resize(renderData.size());
    Render::Graphics::NextRenderData.swap(renderData);
    Semaphore::Signal(NEW_RENDERDATA_PREPARED);

}
void Rain::Rain3DGame::ExitGame() {
    stop = true;
}
void Rain::Rain3DGame::ClearUp() {
    Render::Graphics::ClearUp();
    MeshRender::MeshRenderSystem::GetInstance()->ClearUp();
}
