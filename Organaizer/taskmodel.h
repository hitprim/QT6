#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QObject>
#include <QDate>
#include <QList>


struct Task {
    QString title;
    QDate deadline;
    int progress;
};

class TaskModel : public QObject
{
    Q_OBJECT
public:
    explicit TaskModel(QObject *parent = nullptr);
    Q_INVOKABLE void addTask(const QString& title, const QString& deadline, int progress);
    Q_INVOKABLE void write();
    QList<Task> tasks() const;
    void setTasks(const QList<Task>& tasks);
private:
    QList<Task> m_tasks;

signals:

};

#endif // TASKMODEL_H
