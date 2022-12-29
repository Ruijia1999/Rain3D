#include "Rain3D.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QDockWidget>
#include <QTabWidget>
Rain3D::Rain3D(QWidget *parent)
    : QMainWindow(parent)
{


    ui.setupUi(this);
   
    ui.centralWidget->setMouseTracking(true);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);

    //QWidget* p = takeCentralWidget();
    //if (p) delete p;
    sceneView = new SceneView();
    ui.tabWidget->insertTab(0, sceneView, tr("SceneView"));
    ui.tabWidget->insertTab(1, new ContentBrowser(), tr("SceneView"));
    //QDockWidget* m_projManagerView2 = new QDockWidget(this);
    //m_projManagerView2->setWindowTitle("ss222");
    //this->addDockWidget(Qt::RightDockWidgetArea, m_projManagerView2);
    //m_projManagerView2->setFeatures(QDockWidget::DockWidgetMovable);
    //m_projManagerView2->setAllowedAreas(Qt::RightDockWidgetArea);
    //gameView = new ContentBrowser(this);
    //m_projManagerView2->setWidget(gameView);


}

Rain3D::~Rain3D()
{}



