#include "qmusicwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMusicWidget* w = new QMusicWidget();
    w->show();

    return a.exec();
}
