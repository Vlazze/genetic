#include <QApplication>
#include "mainwindow.h"
#include <ctime>

int main(int argc, char *argv[])
{

    //qsrand((uint)time(0));

    //qt random initialization
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    

    return a.exec();
}
