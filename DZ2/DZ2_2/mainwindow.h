#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QModelIndex m_dragStartPosition;
};
#endif // MAINWINDOW_H
