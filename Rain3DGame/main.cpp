#include "Rain3DGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Rain3DGame w;
    w.show();
    return a.exec();
}
