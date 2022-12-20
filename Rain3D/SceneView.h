#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "ui_SceneView.h"

class SceneView : public QWidget
{
	Q_OBJECT

public:
	SceneView(QWidget *parent = nullptr);
	~SceneView();

	void Initialize();
	void Update();
	void ClearUp();


	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	QPaintEngine* paintEngine() const;
	//Mouse
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:
	Ui::SceneViewClass ui;
};
