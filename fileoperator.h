#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QWidget>
#include <QString>          /* Unicode string */
#include <QStringList>      /* List of strings */
#include <QDir>             /* Informations about the directory */
#include <QFileInfo>        /* Informations about the file */
#include <QFileDialog>      /* File dialog */
#include <QFile>            /* File operations */
#include <QTextStream>      /* Write data from line by line */
#include <QMessageBox>      /* Messagebox for communicating with the user (like C# messagebox) */
#include <QSharedPointer>   /* Smartpointer. Implements garbage collector like memory management */
#include <QList>            /* STL like list */
#include <QSettings>        /* The QSettings class provides persistent platform-independent application settings. */

#include "task.h"

#define DEBUG               /* Debug mode if defined; otherwise normal mode -> no debug messages to the output */

#ifdef DEBUG
#include <QDebug>           /* Class for debugging */
#endif

class FileOperator : public QWidget
{
    Q_OBJECT
private:
    QString m_fileName;
    bool performSaveOperation(QList<QSharedPointer<Task> > list, QString fileName);
    QList<QSharedPointer<Task> > performLoadOperation(QString fileName);
    void newList();
    QSettings m_settings;

public:
    explicit FileOperator(QWidget *parent = 0);
    ~FileOperator();
    void save(QList<QSharedPointer<Task> > list);
    void saveAs(QList<QSharedPointer<Task> > list);
    QList<QSharedPointer<Task> > open();

    QSettings settings() const;
    void setSettings(const QSettings &settings);

    QString fileName() const;
    void setFileName(const QString &fileName);

signals:

public slots:
};

#endif // FILEOPERATOR_H
