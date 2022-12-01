#include "Rain3D.h"
#include <QtWidgets/QApplication>

#include "Render/RenderSystem.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Rain3D w;
    
    w.show();
    return a.exec();
}
