#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTranslator>
#include "fsysv.h"

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

    void on_Read_only_clicked();

    void changeToRus();

    void changeToEng();

    void on_pushButton_NewFile_clicked();

    void quit();

    void setTheme();

    void on_pushButton_clicked();

    void on_pushButton_Print_clicked();

private:
    Ui::MainWindow *ui;
    QString filter;
    bool isReadOnly = false;
    QTranslator translator;
    FSYSV viewer;

};
#endif // MAINWINDOW_H
