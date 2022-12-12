#include "Rain3D.h"
#include "ECS/World.h"
#include "Input/Input.h"
#include <QPushButton>
#include <QMouseEvent>
#include <functional>
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"
#include "Render/RenderData.h"
#include "Render/Graphics.h"
#include "Time/Time.h"
using namespace std::placeholders;
using namespace Rain;
namespace {
    std::vector<Rain::Render::RenderData> RenderData;
    uint64_t timeLastFrame;
}

Rain3D::Rain3D(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    setFixedSize(QSize(1600, 900));
    setWindowTitle("Rain3D");
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    ui.centralWidget->setMouseTracking(true);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
    Initialize();


}

Rain3D::~Rain3D()
{}



void Rain3D::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        Rain::Input::Mouse::OnMouseLeftDown();
    }
    else if (event->button() == Qt::RightButton) {
        Rain::Input::Mouse::OnMouseRightDown();
    } else if (event->button() == Qt::MidButton) {
        Rain::Input::Mouse::OnMouseMidDown();
    }
   
}

void Rain3D::mouseReleaseEvent(QMouseEvent* event) {
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

void Rain3D::mouseMoveEvent(QMouseEvent* event) {
    Rain::Input::Mouse::OnMouseMove(event->x(), event->y());
}

void Rain3D::paintEvent(QPaintEvent* event)
{

    Update();
    update();
}

void Rain3D::resizeEvent(QResizeEvent* event)
{
   
}

void Rain3D::Initialize() {
    Rain::Input::Initialize();
    Rain::Render::RenderSystem::Initialize((HWND)winId());
   
    timeLastFrame = 0;
    GameObject::GameObjectSystem::GetInstance()->Initialize();
    GameObject::GameObjectSystem::GetInstance()->AddComponent(new GameObject::GameObjectComponent(0));
    Transform::TransformSystem::GetInstance()->Initialize();
    Transform::TransformSystem::GetInstance()->AddComponent(new Transform::TransformComponent(Math::Vector3(2,0,0), Math::Vector3(1, 1, 1), Math::Vector3(0, 0, 0)));
    Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [](Input::MouseInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(0);
        transform->m_Position = transform->m_Position + Math::Vector3(0.1f, 0, 0);
        });
}

void Rain3D::Update() {
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


    RenderData.clear();
    std::vector<GameObject::GameObjectComponent*> gameobjects = GameObject::GameObjectSystem::GetInstance()->GetAllComponents<GameObject::GameObjectComponent>();
    for (auto go : gameobjects) {
    	if (go->m_isActive) {
    		Render::ConstantBuffer::VSConstantBuffer vsConstantBuffer;
    		Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(go->id);
    		vsConstantBuffer.transform_cameraToProjected = Math::CreateCameraToProjectedTransform_perspective(1.5708f, 1, 1, 10);
    		vsConstantBuffer.transform_localToWorld = Math::CreateLocalToWorldTransform(Math::Quaternion(), transform->m_Position);
    		vsConstantBuffer.transform_localToWorld.Inverse();
    		vsConstantBuffer.transform_worldToCamera = Math::CreateWorldToCameraTransform(Math::Quaternion(), Math::Vector3(0, 0, 10));
    		vsConstantBuffer.transform_worldToCamera.Inverse();
    		RenderData.push_back(Render::RenderData(s_mesh, s_effect, vsConstantBuffer));
    	}

    }

    Render::Graphics::NextRenderData.resize(RenderData.size());
    Render::Graphics::NextRenderData.swap(RenderData);
    Rain::Render::RenderSystem::Update();


}

void Rain3D::ClearUp() {
    int j = 0;
}