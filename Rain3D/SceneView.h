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
	static void StartGame();
	static void Update();
	void ClearUp();

	//Mouse
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:
	Ui::SceneViewClass ui;
};
