#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QListWidgetItem>
#include <QCompleter>           /* The QCompleter class provides completions based on an item model. */
#include <QStringListModel>     /* The QStringListModel class provides a model that supplies strings to views. */


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

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_modifyButton_clicked();

    void appFocusChanged(QWidget *old, QWidget *now);

private:
    Ui::MainWindow *ui;
    FileOperator *m_fileOperator;
    QList<QSharedPointer<Task> > m_tasks;
    QCompleter *m_completer;
    QStringListModel *m_copmleterModel;
    QStringList categories();

};

#endif // MAINWINDOW_H
