#include "task.h"


QString Task::category() const
{
    return m_category;
}

void Task::setCategory(const QString &category)
{
    m_category = category;
}

QString Task::job() const
{
    return m_job;
}

void Task::setJob(const QString &job)
{
    m_job = job;
}

Task::Task(QObject *parent) : QObject(parent)
{

}

Task::Task(const QString &job, const QString &cat, QObject *parent): QObject(parent),
    m_job(job),
    m_category(cat)
{

}

Task::~Task()
{

}
