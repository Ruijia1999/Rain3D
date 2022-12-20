#ifndef RAIN3D
#define RAIN3D

#include <QtWidgets/QMainWindow>
#include "ui_Rain3D.h"
#include "SceneView.h"
#include "ContentBrowser.h"
class Rain3D : public QMainWindow
{
    Q_OBJECT

public:
    
    Rain3D(QWidget* parent = nullptr);
    ~Rain3D();
    

private:
    QPaintEngine* paintEngine() const { return 0; }



    //Keyboard
private:
    Ui::Rain3DClass ui;
    SceneView* sceneView;
    ContentBrowser* gameView;
};

#endif // Rain3D

