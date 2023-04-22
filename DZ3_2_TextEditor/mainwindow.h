#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QString>

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
    void on_pushButton_Save_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_ref_clicked();

    void on_backButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filter;
};
#endif // MAINWINDOW_H
