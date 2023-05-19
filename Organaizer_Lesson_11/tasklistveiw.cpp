#include "tasklistveiw.h"
#include <QTableView>
#include <QVBoxLayout>


TaskListVeiw::TaskListVeiw(TaskModel *model, QWidget *parent)
    : QMainWindow{parent}, taskModel{model}
{
    QTableView* table = new QTableView;
    //table->setModel(taskModel);
    table->resizeColumnsToContents();

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(table);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

}
