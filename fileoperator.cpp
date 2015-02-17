#include "fileoperator.h"

FileOperator::FileOperator(QWidget *parent) : QWidget(parent)
{
    if(m_settings.contains("GeneralSettings/ListFileName"))
    {
        m_fileName = m_settings.value("GeneralSettings/ListFileName").toString();

#ifdef DEBUG
        qDebug() << "variable m_fileName: " << m_fileName;
#endif

    }
    else m_fileName = "";
}

FileOperator::~FileOperator()
{

}

void FileOperator::save(QList<QSharedPointer<Task> > list)
{
    if(m_fileName.isEmpty()) saveAs(list);
    else performSaveOperation(list, m_fileName);
}

void FileOperator::saveAs(QList<QSharedPointer<Task> > list)
{
    QString path = QDir::homePath();
    if(m_fileName != "")
    {
        QFileInfo info(m_fileName);
        path = info.absolutePath();
    }

    QString fn = QFileDialog::getSaveFileName(
                this,
                tr("Save As..."),
                path,
                tr("ToDoList files (*.tdlst);;Text files (*.txt);;All files (*.*)"));

    if(!fn.isEmpty())
    {
        QFileInfo info(fn);
        QString ext = info.suffix();
        if(ext != "tdlst" && ext != "txt") fn += ".tdlst";
        performSaveOperation(list, fn);
    }
}

QList<QSharedPointer<Task> > FileOperator::open()
{
    QString fn;

    if(m_fileName == "")
    {
        QString path = QDir::homePath();
        QFileInfo info(m_fileName);
        path = info.absolutePath();

        fn = QFileDialog::getOpenFileName(
                    this,
                    tr("Open File..."),
                    path,
                    tr("ToDoList files (*.tdlst);;Text files (*.txt)"));

    }
    else fn = m_fileName;

#ifdef DEBUG
        qDebug() << "Open: " << fn;
#endif

    QList<QSharedPointer<Task> > list;
    if(!fn.isEmpty()) list = performLoadOperation(fn);
    return list;
}


QString FileOperator::fileName() const
{
    return m_fileName;
}

void FileOperator::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}
bool FileOperator::performSaveOperation(QList<QSharedPointer<Task> > list, QString fileName)
{
    QFile file(fileName);
    bool success = false;

    if(file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) // open file for write, truncate and with text type
    {
        QTextStream out(&file);
        for (int i = 0; i < list.count(); ++i) out << list.at(i)->job() << "|" << list.at(i)->category() << endl;
        if(file.error() == 0) success = true;
    }

    if(success)
    {
        m_fileName = fileName;
        m_settings.setValue("GeneralSettings/ListFileName", fileName);
#ifdef DEBUG
        qDebug() << "Setting GeneralSettings/ListFileName to " << m_fileName;
#endif
    }
    else
    {
        QMessageBox *mb = new QMessageBox(
                    QMessageBox::Critical,
                    tr("Unable To Save"),
                    tr("Something happened while saving the file. Maybe it's write protected..."));
        mb->exec();
        delete mb;
    }

#ifdef DEBUG
    qDebug() << "Saving to: " << fileName;
#endif

    return success;
}

QList<QSharedPointer<Task> > FileOperator::performLoadOperation(QString fileName)
{
    QList<QSharedPointer<Task> > list;
#ifdef DEBUG
        qDebug() << "PerformLoad: " << fileName;
#endif
    QFile file(fileName);
    bool success = false;

    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QStringList sl = in.readLine().split("|");
            list.append(QSharedPointer<Task>(new Task(sl.at(0), sl.at(1))));
        }
        if(file.error() == 0) success = true;
    }

#ifdef DEBUG
        qDebug() << "PerformLoad success: " << success;
#endif

    if(success) m_fileName = fileName;
    else
    {
        QMessageBox *mb = new QMessageBox(
                    QMessageBox::Critical,
                    tr("Unable To Open"),
                    tr("Unable to read the file!"));
        mb->exec();
        delete mb;
    }
    newList();
    return list;
}

void FileOperator::newList()
{
    m_fileName = "";
}

