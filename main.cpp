#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w,p;
    w.show();
    w.setFixedSize(320,480);
    w.setWindowTitle("Red and Black Judges");

    return a.exec();
}
