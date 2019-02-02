#include "doomfire.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DoomFire d;
    d.showNormal();
    return a.exec();
}
