#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Rain3D.h"
#include "Render/RenderSystem.h"
class Rain3D : public QMainWindow
{
    Q_OBJECT

public:
    Rain3D(QWidget *parent = nullptr);
    ~Rain3D();


    virtual QPaintEngine* paintEngine() const { return 0; }
	
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
private:
    Ui::Rain3DClass ui;
};
