#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableView>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    Q_INVOKABLE void showMainWindow();

private:
    QSqlQueryModel* model;
    QTableView* view;

};

#endif // MAINWINDOW_H
