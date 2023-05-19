#ifndef TASKLISTVEIW_H
#define TASKLISTVEIW_H

#include <QMainWindow>
#include "taskmodel.h"

class TaskListVeiw : public QMainWindow
{
    Q_OBJECT
public:
    explicit TaskListVeiw(TaskModel* model, QWidget *parent = nullptr);
    ~TaskListVeiw();

private:
    TaskModel *taskModel;

};

#endif // TASKLISTVEIW_H
