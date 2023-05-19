#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QObject>
#include <QDate>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QAbstractTableModel>
#include <QSqlQueryModel>


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
    Q_INVOKABLE int getCount();
    Q_INVOKABLE void saveDB();
    QList<Task> tasks() const;
    void setTasks(const QList<Task>& tasks);
    void setCount(int newCount);

private:
    QList<Task> m_tasks;
    QAbstractTableModel *m_taskModel;
    int count;


signals:

};

#endif // TASKMODEL_H
