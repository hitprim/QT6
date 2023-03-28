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
    int c = ui->lineEdit_3->text().toInt();

    int D = qPow(b, 2) - 4*a*c;

    QString answer, answer1;

    if (a == 0){
        answer = QString::number((-1)*c);
        ui->lineEdit_4->setText(answer);
    }
    else if (D < 0){
        ui->lineEdit_4->setText("Нет корней");
    }
    else if(D == 0){
        answer = QString::number((-b/(2*a)));
        ui->lineEdit_4->setText(answer);
    }
    else if (D > 0) {
        answer = QString::number(((-b) + qSqrt(D)) / 2*a);
        answer1 = QString::number(((-b) - qSqrt(D)) / 2*a);
        QString str = "x1: %1  x2: %2";
        str = str.arg(answer, answer1);
        ui->lineEdit_4->setText(str);
    }

}

