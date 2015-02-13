#include "fileoperator.h"

FileOperator::FileOperator(QWidget *parent) : QWidget(parent)
{

}

FileOperator::~FileOperator()
{

}

void FileOperator::save(QList<QSharedPointer<Task> > list)
{
    if(_fileName.isEmpty()) saveAs(list);
    else performSaveOperation(list, _fileName);
}

void FileOperator::saveAs(QList<QSharedPointer<Task> > list)
{
    QString path = QDir::homePath();
    if(_fileName != "")
    {
        QFileInfo info(_fileName);
        path = info.absolutePath();
    }

    QString fn = QFileDialog::getSaveFileName(
                this,
                "Mentés másként...",
                path,
                "ToDoList-fájlok (*tdlst);;Szövegfájlok (*txt);;Minden fájl (*)");

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
    QString path = QDir::homePath();
    if(_fileName != "")
    {
        QFileInfo info(_fileName);
        path = info.absolutePath();
    }

    QString fn = QFileDialog::getOpenFileName(
                this,
                "Fájl megnyitása...",
                path,
                "ToDoList-fájlok (*.tdlst);;Szövegfájlok (*.txt)");


    QList<QSharedPointer<Task> > list;
    if(!fn.isEmpty()) list = performLoadOperation(fn);
    return list;
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

    if(success) _fileName = fileName;
    else
    {
        QMessageBox *mb = new QMessageBox(
                    QMessageBox::Critical,
                    "Nem sikerült a mentés",
                    "Valami hiba történt a file mentése közben (talán írásvédett a file...?)!");
        mb->exec();
        delete mb;
    }

#ifdef DEBUG
    qDebug() << "Saving to: " << fileName;
#endif
    Q_UNUSED(list);

    return success;
}

QList<QSharedPointer<Task> > FileOperator::performLoadOperation(QString fileName)
{
    QList<QSharedPointer<Task> > list;
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

    if(success) _fileName = fileName;
    else
    {
        QMessageBox *mb = new QMessageBox(
                    QMessageBox::Critical,
                    "Nem sikerült a megnyitás",
                    "Valami hiba történt a file megynitása közben. Nem lehet olvasni a file-t!");
        mb->exec();
        delete mb;
    }
    newList();
    return list;
}

void FileOperator::newList()
{
    _fileName = "";

}
