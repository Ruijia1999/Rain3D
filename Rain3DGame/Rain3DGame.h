#ifndef RRAIN3DGAME
#define RRAIN3DGAME

#include <QtWidgets/QMainWindow>
#include "ui_Rain3DGame.h"

class Rain3DGame : public QMainWindow
{
    Q_OBJECT

public:
    Rain3DGame(QWidget* parent = nullptr);
    ~Rain3DGame();
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
private:
    Ui::Rain3DGameClass ui;
};

#endif // !1

