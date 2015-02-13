#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "fileoperator.h"

#ifdef DEBUG
#include <QDebug>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    FileOperator *m_fileOperator;
    QList<QSharedPointer<Task> > tasks;

};

#endif // MAINWINDOW_H
