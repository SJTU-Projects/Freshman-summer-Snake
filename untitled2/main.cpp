#include "window.h"
#include <QApplication>
#include "test.h"
#include <QtGui>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    QApplication a(argc, argv);
    Window w;
    w.show();

    //SnakeWindow clock;//钟表实例
    //clock.show();

    return a.exec();
}
