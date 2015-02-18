#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QListWidgetItem>
#include <QCompleter>           /* The QCompleter class provides completions based on an item model. */
#include <QStringListModel>     /* The QStringListModel class provides a model that supplies strings to views. */
#include <QCoreApplication>     /* The QCoreApplication class provides an event loop for console Qt applications. */
#include <QTimer>               /* The QTimer class provides repetitive and single-shot timers. */

#include "fileoperator.h"
#include "diagramcreator.h"
#include "defines.h"
#include "aboutwindow.h"        /* My own class for About window */
#include "settingswindow.h"     /* My own class for Settings window */

namespace Ui
{
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

    void showJobsHavingCategory(const QString &text);

    void on_tabWidget_currentChanged(int index);

    void on_actionAbout_triggered();

    void on_actionNew_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    FileOperator *m_fileOperator;
    DiagramCreator *m_diagramCreator;
    QList<QSharedPointer<Task> > m_tasks;
    QCompleter *m_completer;
    QStringListModel *m_copmleterModel;
    AboutWindow *m_aboutWindow;
    QStringList categories();
    void loadAutoSaveSettings();
    QTimer *m_timer;

};

#endif // MAINWINDOW_H
