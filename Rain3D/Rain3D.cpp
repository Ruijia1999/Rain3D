#include "Rain3D.h"
#include "ECS/World.h"
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
   
    Rain::Render::RenderSystem::Initialize((HWND)winId());
    Rain::ECS::World::GetInstance()->Initialize();
}

Rain3D::~Rain3D()
{}

void Rain3D::paintEvent(QPaintEvent* event)
{
    Rain::ECS::World::GetInstance()->Update();
    Rain::Render::RenderSystem::Update();

    update();
}
void Rain3D::resizeEvent(QResizeEvent* event)
{
   
}