#include "SceneView.h"
#include "Render/RenderSystem.h"
#include "Event/EventBase.h"
#include <functional>
#include <map>
#include <string>
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"
#include "Render/RenderData.h"
#include "Render/Graphics.h"
#include "Time/Time.h"
#include "Asset/SceneLoader.h"
#include "EngineLog/EngineLog.h"
#include "MeshRender/MeshRender.h"
#include "ECS/World.h"
#include "Input/Input.h"
#include "Reflect/Reflect.h"
using namespace std::placeholders;
using namespace Rain;
namespace {
    std::vector<Rain::Render::RenderData> RenderData;
    uint64_t timeLastFrame;

    //std::map<std::string, Render::Mesh*> meshes;
    //std::map<std::string, Render::Effect*> effects;

}

SceneView::SceneView(QWidget *parent)
	: QWidget(parent)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);

   
    Initialize();
}

SceneView::~SceneView()
{}
void SceneView::Initialize() {
    Rain::EngineLog::CreateLogFile("ss");

    Rain::Input::Initialize();
    Rain::Render::RenderSystem::Initialize((HWND)winId());

    GameObject::GameObjectSystem::GetInstance()->Initialize();
    Transform::TransformSystem::GetInstance()->Initialize();
    MeshRender::MeshRenderSystem::GetInstance()->Initialize();

    Rain::Asset::SceneLoader::RegisterComponentCreators();
    Rain::Asset::SceneLoader::LoadScene("ss");

    timeLastFrame = 0;

}

void SceneView::Update() {
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

    //Init Constant Buffer
    RenderData.clear();
    std::vector<GameObject::GameObjectComponent*> gameobjects = GameObject::GameObjectSystem::GetInstance()->GetAllComponents<GameObject::GameObjectComponent>();
    for (int i = 0; i < 2; i++) {
        GameObject::GameObjectComponent* go = gameobjects[i];
        if (go->isActive) {

            Render::ConstantBuffer::VSConstantBuffer vsConstantBuffer;
            Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(go->id);
            vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(1.5708f, 1, 1, 12);
            vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(Math::Quaternion(), transform->position);
            vsConstantBuffer.transform_localToWorld.Inverse();
            vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(Math::Quaternion(), Math::Vector3(0, 0, 10));
            vsConstantBuffer.transform_worldToCamera.Inverse();
            MeshRender::MeshRenderComponent* meshRender = MeshRender::MeshRenderSystem::GetInstance()->GetComponent<MeshRender::MeshRenderComponent>(go->id);
            RenderData.push_back(Render::RenderData(meshRender->mesh, meshRender->effect, vsConstantBuffer));
        }
    }
    Render::Graphics::NextRenderData.resize(RenderData.size());
    Render::Graphics::NextRenderData.swap(RenderData);
    Rain::Render::RenderSystem::Update();
}

void SceneView::ClearUp() {
    int j = 0;
}



void SceneView::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {
        Rain::Input::Mouse::OnMouseLeftDown();
    }
    else if (event->button() == Qt::RightButton) {
        Rain::Input::Mouse::OnMouseRightDown();
    }
    else if (event->button() == Qt::MidButton) {
        Rain::Input::Mouse::OnMouseMidDown();
    }
}

void SceneView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Rain::Input::Mouse::OnMouseLeftUp();
    }
    else if (event->button() == Qt::RightButton) {
        Rain::Input::Mouse::OnMouseRightUp();
    }
    else if (event->button() == Qt::MidButton) {
        Rain::Input::Mouse::OnMouseMidUp();
    }
}

void SceneView::mouseMoveEvent(QMouseEvent* event) {
    Rain::Input::Mouse::OnMouseMove(event->x(), event->y());
}

void SceneView::paintEvent(QPaintEvent* event)
{
    Update();
    update();
}

void SceneView::resizeEvent(QResizeEvent* event)
{

}

QPaintEngine* SceneView::paintEngine() const {
    return NULL;
}