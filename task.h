#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task : public QObject
{
    Q_OBJECT
private:
    QString m_job;
    QString m_category;

public:
    explicit Task(QObject *parent = 0);
    explicit Task(const QString &job, const QString &cat, QObject *parent = 0);
    ~Task();

    QString category() const;
    void setCategory(const QString &category);

    QString job() const;
    void setJob(const QString &job);

signals:

public slots:
};

#endif // TASK_H
