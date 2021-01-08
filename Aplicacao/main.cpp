#include "ihm_drone.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHM_Drone w;
    w.show();
    return a.exec();
}
