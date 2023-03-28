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
    int a = ui->lineEdit->text().toInt();
    int b = ui->lineEdit_2->text().toInt();
    double angle = ui->lineEdit_3->text().toDouble();


    if(ui->radioButton_2->isChecked()){
        angle = qDegreesToRadians(angle);
    }

    QString answer = QString::number(qSqrt(qPow(a,2)+qPow(b,2)-2*a*b*qCos(angle)));

    ui->lineEdit_4->setText(answer);
}

