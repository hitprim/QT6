#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //ui->textEdit_2->clear();
    QString first_win = ui->textEdit->toPlainText();
    ui->textEdit_2->append(first_win);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    QString sec_win = ui->textEdit_2->toPlainText();
    ui->textEdit_2->clear();
    ui->textEdit->append(sec_win);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setHtml("<font color='red'>Hello</font>");
}

