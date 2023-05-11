#include "taskmodel.h"

TaskModel::TaskModel(QObject *parent)
    : QObject{parent}
{

}

void TaskModel::addTask(const QString &title, const QString &deadline, int progress)
{
    Task task;
    task.title = title;
    task.deadline = QDate::fromString(deadline, "d.MM.yyyy");
    task.progress = progress;
    m_tasks.append(task);
}

void TaskModel::write()
{
    for(auto &task : m_tasks) {

        qDebug() << task.title << ";" << task.deadline << ";" << task.progress;

    }
}

QList<Task> TaskModel::tasks() const
{
    return m_tasks;
}

void TaskModel::setTasks(const QList<Task> &tasks)
{
    m_tasks = tasks;
}
