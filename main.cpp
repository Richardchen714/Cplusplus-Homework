#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    //设置窗口标题
    w.setWindowTitle("Bus Booking System");
    w.show();
    return a.exec();
}
