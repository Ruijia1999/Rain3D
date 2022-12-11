#include "Rain3D.h"
#include "ECS/World.h"
#include "Input/Input.h"
#include <QPushButton>
#include <QMouseEvent>
#include <functional>
using namespace std::placeholders;
Rain3D::Rain3D(QWidget *parent)
    : QMainWindow(parent)
{
    Rain::Input::Initialize();
    ui.setupUi(this);
    setFixedSize(QSize(1600, 900));
    
    setWindowTitle("Rain3D");

    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    Rain::Render::RenderSystem::Initialize((HWND)winId());
    Rain::ECS::World::GetInstance()->Initialize();
}

Rain3D::~Rain3D()
{}

void Initialize() {

}
void Update() {

}
void ClearUp() {

}

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
    Rain::ECS::World::GetInstance()->Update();
    Rain::Render::RenderSystem::Update();

    update();
}

void Rain3D::resizeEvent(QResizeEvent* event)
{
   
}