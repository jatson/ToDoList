#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QCoreApplication>

#include "defines.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTranslator translator;
    QString locale = QLocale::system().name();
#ifdef DEBUG
    qDebug() << QDir::toNativeSeparators(QString(QCoreApplication::applicationDirPath() + "/ToDoList_") + locale + QString(".qm"));
#endif

    if(!translator.load(QDir::toNativeSeparators(QString(QCoreApplication::applicationDirPath() + "/ToDoList_") + locale + QString(".qm"))))
    {
#ifdef DEBUG
        qDebug() << "Translation cannot be opened...";
    }
    else
    {
        qDebug() << "Traslation loaded";
#endif
    }

    QObject::connect(&a, SIGNAL(focusChanged(QWidget*, QWidget*)),
                     &w, SLOT(appFocusChanged(QWidget*,QWidget*)));

    w.show();

    a.installTranslator(&translator);
    return a.exec();
}
