#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->jobEdit, SIGNAL(returnPressed()),
            ui->addButton, SLOT(click()));

    m_fileOperator = new FileOperator(NULL);
#ifdef DEBUG
    QObject::dumpObjectInfo();
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
#ifdef DEBUG
    qDebug() << "addButton clicked";
#endif
    if(!ui->jobEdit->text().isEmpty())
    {
        ui->listWidget->addItem(ui->jobEdit->text().simplified());
        tasks.append(QSharedPointer<Task>(new Task(ui->jobEdit->text(), "default category")));
#ifdef DEBUG
        qDebug() << "jobEdit was not empty: " << ui->jobEdit->text();
#endif
        ui->jobEdit->clear();
        ui->jobEdit->setFocus();

    }
#ifdef DEBUG
    else qDebug() << "jobEdit was empty";
#endif
}

void MainWindow::on_removeButton_clicked()
{
#ifdef DEBUG
    qDebug() << "removeButton clicked";
#endif
    int idx = ui->listWidget->currentRow();
    delete ui->listWidget->takeItem(idx);
    tasks.removeAt(idx);
}

void MainWindow::on_actionSave_triggered()
{
    m_fileOperator->save(tasks);
}

void MainWindow::on_actionSaveAs_triggered()
{
    m_fileOperator->saveAs(tasks);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionOpen_triggered()
{
#ifdef DEBUG
    qDebug() << "actionOpen triggered";
#endif
    tasks.clear();
    tasks = m_fileOperator->open();

    if(!tasks.isEmpty())
    {
        ui->listWidget->clear();
        QListIterator<QSharedPointer<Task> > ji(tasks);
        while(ji.hasNext()) ui->listWidget->addItem(ji.next()->job());
    }
}
