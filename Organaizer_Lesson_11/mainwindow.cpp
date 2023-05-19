#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{

}

void MainWindow::showMainWindow()
{



    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is open";
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM tasks")) {
        qWarning() << "Success to execute query";
        return;
    }

    model = new QSqlQueryModel(this);

    model->setQuery(std::move(query));



    view = new QTableView(this);
    view->setModel(model);
    setCentralWidget(view);
    view->show();

    resize(400, 400);

    show();
}
