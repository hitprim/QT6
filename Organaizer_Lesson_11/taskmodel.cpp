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
    count++;
    m_tasks.append(task);
}

void TaskModel::write()
{
    for(auto &task : m_tasks) {

        qDebug() << task.title << ";" << task.deadline << ";" << task.progress;

    }
}


void TaskModel::saveDB()
{
    QSqlQuery deleteQuery(QSqlDatabase::database());
    if (!deleteQuery.exec("DELETE FROM tasks")) {
        qWarning() << "Failed to delete tasks:" << deleteQuery.lastError().text();
    }
    QSqlQuery insertQuery(QSqlDatabase::database());
    insertQuery.prepare("INSERT INTO tasks (Task, Deadline, Progress) VALUES (:Task, :Deadline, :Progress);");
    for (const Task& task : m_tasks) {
        insertQuery.bindValue(":Task", task.title);
        insertQuery.bindValue(":Deadline", task.deadline.toString("d.MM.yyyy"));
        insertQuery.bindValue(":Progress", task.progress);
        if (!insertQuery.exec()) {
            qWarning() << "Failed to insert task:" << insertQuery.lastError().text();
        }
    }
}




int TaskModel::getCount()
{
    return count;
}

QList<Task> TaskModel::tasks() const
{
    return m_tasks;
}

void TaskModel::setTasks(const QList<Task> &tasks)
{
    m_tasks = tasks;
}

void TaskModel::setCount(int newCount)
{
    count = newCount;
}
