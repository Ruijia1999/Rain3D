#ifndef RAIN3D
#define RAIN3D

#include <QtWidgets/QMainWindow>
#include "ui_Rain3D.h"
#include "Render/RenderSystem.h"
#include "Event/EventBase.h"
class Rain3D : public QMainWindow
{
    Q_OBJECT

public:
    Rain3D(QWidget* parent = nullptr);
    ~Rain3D();

protected:
    void Initialize();
    void Update();
    void ClearUp();
private:
    QPaintEngine* paintEngine() const { return 0; }

    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

    //Mouse
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    //Keyboard
private:
    Ui::Rain3DClass ui;
};

#endif // Rain3D

