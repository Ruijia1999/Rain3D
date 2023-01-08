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
#include "AI/NavMesh.h"
using namespace std::placeholders;
using namespace Rain;
namespace {
    std::vector<Rain::Render::RenderData> RenderData;
    uint64_t timeLastFrame;
    bool stop;
    std::thread* mainGameThread;
}

void Rain3DGame::StartGame() {
    stop = false;
    while (!stop) {
        Update();
    }
    int exit = 1;
}

void Rain3DGame::Initialize(HWND hWnd, int width, int height) {
    AI::NavMesh mesh;
    std::vector<Math::Vector2> vertices;
    vertices.push_back(Math::Vector2(0, 0));
    vertices.push_back(Math::Vector2(3, 6));
    vertices.push_back(Math::Vector2(7, 4));
    vertices.push_back(Math::Vector2(6, 1));
    vertices.push_back(Math::Vector2(5, 2));
    vertices.push_back(Math::Vector2(3, 2));

    AI::Polygon polygon(vertices);
    mesh.polygonData = polygon;
    mesh.GenerateNavMesh();
    Rain::EngineLog::CreateLogFile("log");

    Rain::Input::Initialize();
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

void Rain3DGame::Update() {
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
    ColliderSystem::GetInstance()->Update(timeSinceLastFrame);
    //Init Constant Buffer
    RenderData.clear();
    std::vector<GameObject::GameObjectComponent*> gameobjects = GameObject::GameObjectSystem::GetInstance()->GetAllComponents<GameObject::GameObjectComponent>();
    for (int i = 0; i < 2; i++) {
        GameObject::GameObjectComponent* go = gameobjects[i];
        if (go->isActive) {

            Render::ConstantBuffer::VSConstantBuffer vsConstantBuffer;
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(go->id);
            vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(1, 120, 1.57079632, 1.02477892);
            vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(Math::Quaternion(0, 0,0, 1), transform->position);
            vsConstantBuffer.transform_localToWorld.Inverse();
            vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(Math::Quaternion(-0.7068252, 0, 0, 0.7073883), Math::Vector3(0, 0, -55));
            vsConstantBuffer.transform_worldToCamera.Inverse();
            MeshRender::MeshRenderComponent* meshRender = MeshRender::MeshRenderSystem::GetInstance()->GetComponent<MeshRender::MeshRenderComponent>(go->id);
            RenderData.push_back(Render::RenderData(meshRender->mesh, meshRender->effect, vsConstantBuffer));
            Math::Vector4 vec(meshRender->mesh->vertexData[0].x, meshRender->mesh->vertexData[0].y, meshRender->mesh->vertexData[0].z, 1);
            vec = vsConstantBuffer.transform_localToWorld * vec;
            vec = vsConstantBuffer.transform_worldToCamera * vec;
            vec = vsConstantBuffer.transform_cameraToProjected * vec;
            vec = vec / vec[3];
            int j = 1;
        }
    }
    Render::Graphics::NextRenderData.resize(RenderData.size());
    Render::Graphics::NextRenderData.swap(RenderData);
    Rain::Render::RenderSystem::Update();
}
void Rain3DGame::ExitGame() {
    stop = true;
}
void Rain3DGame::ClearUp() {
    int j = 0;
}