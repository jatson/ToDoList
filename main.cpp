#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QObject::connect(&a, SIGNAL(focusChanged(QWidget*, QWidget*)),
                     &w, SLOT(appFocusChanged(QWidget*,QWidget*)));

    w.show();

    return a.exec();
}
