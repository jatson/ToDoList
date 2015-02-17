#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* Init for saving programsettings (registry in windows) */
    QCoreApplication::setOrganizationName("Barni Qt tanulmánya");
    QCoreApplication::setOrganizationDomain("example.com");
    QCoreApplication::setApplicationName("ToDoList");

    ui->setupUi(this);


    connect(ui->jobEdit, SIGNAL(returnPressed()),
            ui->addButton, SLOT(click()));
    connect(ui->categoryEdit, SIGNAL(returnPressed()),
            ui->addButton, SLOT(click()));
    connect(ui->searchEdit, SIGNAL(textChanged(QString)),
            this, SLOT(showJobsHavingCategory(QString)));

    m_fileOperator = new FileOperator(NULL);
    if(m_fileOperator->fileName() != "") on_actionOpen_triggered();

    m_copmleterModel = new QStringListModel(this);
    m_completer = new QCompleter(m_copmleterModel, this);
    m_diagramCreator = new DiagramCreator(this);
    ui->graphicsView->setScene(m_diagramCreator->scene());
    ui->categoryEdit->setCompleter(m_completer);
    ui->searchEdit->setCompleter(m_completer);

#ifdef DEBUG
    QObject::dumpObjectInfo();
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_fileOperator;
    delete m_completer;
    delete m_diagramCreator;
    if(m_aboutWindow) delete m_aboutWindow;
}

void MainWindow::on_addButton_clicked()
{
#ifdef DEBUG
    qDebug() << "addButton clicked";
#endif
    if(!ui->jobEdit->text().isEmpty() && !ui->categoryEdit->text().isEmpty())
    {
        ui->listWidget->addItem(ui->jobEdit->text().simplified());
        m_tasks.append(QSharedPointer<Task>(new Task(ui->jobEdit->text().simplified(), ui->categoryEdit->text().simplified())));
#ifdef DEBUG
        qDebug() << "jobEdit was not empty: " << ui->jobEdit->text().simplified();
#endif
        ui->jobEdit->clear();
        ui->categoryEdit->clear();
        ui->jobEdit->setFocus();
    }
    else
    {
        QSharedPointer<QMessageBox> mb(new QMessageBox(
                    QMessageBox::Critical,
                    tr("Error"),
                    tr("You have to fill every lines!")));
        mb->exec();
        ui->jobEdit->setFocus();
    }
}

void MainWindow::on_removeButton_clicked()
{
#ifdef DEBUG
    qDebug() << "removeButton clicked";
#endif
    int idx = ui->listWidget->currentRow();
    delete ui->listWidget->takeItem(idx);
    m_tasks.removeAt(idx);
}

void MainWindow::on_actionSave_triggered()
{
    m_fileOperator->save(m_tasks);
}

void MainWindow::on_actionSaveAs_triggered()
{
    m_fileOperator->saveAs(m_tasks);
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
    m_tasks.clear();
    m_tasks = m_fileOperator->open();

    if(!m_tasks.isEmpty())
    {
        ui->listWidget->clear();
        QListIterator<QSharedPointer<Task> > ji(m_tasks);
        while(ji.hasNext()) ui->listWidget->addItem(ji.next()->job());
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int idx = ui->listWidget->row(item);
    ui->jobEdit->setText(m_tasks.at(idx)->job());
    ui->categoryEdit->setText(m_tasks.at(idx)->category());
}

void MainWindow::on_modifyButton_clicked()
{
    QString jobTxt = ui->jobEdit->text().simplified();
    QString categoryTxt = ui->categoryEdit->text().simplified();
    if(!jobTxt.isEmpty() && !categoryTxt.isEmpty())
    {
        int idx = ui->listWidget->currentRow();
        m_tasks[idx]->setJob(jobTxt);
        m_tasks[idx]->setCategory(categoryTxt);

        ui->listWidget->currentItem()->setText(jobTxt);
    }
    else
    {
        QSharedPointer<QMessageBox> mb(new QMessageBox(
                    QMessageBox::Critical,
                    tr("Error"),
                    tr("You cannot leave any fields empty. If you want use delete function!")));
        mb->exec();
        ui->jobEdit->setFocus();
    }
}

void MainWindow::appFocusChanged(QWidget *old, QWidget *now)
{
    Q_UNUSED(old); // make compiler happy
    if(now == ui->categoryEdit || now == ui->searchEdit) m_copmleterModel->setStringList(categories());
#ifdef DEBUG
    qDebug() << "focus changed from " << old << " to " << now;
#endif

}

QStringList MainWindow::categories()
{
    QStringList list;
    for (int i = 0; i < m_tasks.size(); ++i)
    {
        QString category = m_tasks[i]->category();
        if(!list.contains(category)) list << category;
    }
    return list;
}

void MainWindow::showJobsHavingCategory(const QString &text)
{
#ifdef DEBUG
    qDebug() << "editingFinished ";
#endif
    ui->listWidget_2->clear();

    for (int i = 0; i < m_tasks.size(); ++i) if(m_tasks[i]->category() == text) ui->listWidget_2->addItem(m_tasks[i]->job());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2 && !m_tasks.isEmpty()) m_diagramCreator->drawDiagram(m_tasks);
}

void MainWindow::on_actionAbout_triggered()
{
    if(!m_aboutWindow) m_aboutWindow = new AboutWindow(this);
    m_aboutWindow->show(); // modeless window running
    //m_aboutWindow->exec(); // modal window running
}
