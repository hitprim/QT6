#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QDataStream>
#include <QHash>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>



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
    QString filename = QFileDialog::getOpenFileName(this, tr("Mail parser"), QDir::currentPath(), tr("HTML файлы (*.html)"));

    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось открыть файл"));
        return;
    }

    QTextStream in(&file);
    html = in.readAll();

    // Закрыть файл
    file.close();

    //ui->textBrowser->setHtml(html);
    ui->plainTextEdit->setPlainText(html);
}

void MainWindow::on_pushButton_GetData_clicked()
{
    QStringList data = getData(html);
    ui->lineEdit_USD->setText(data[0]);
    ui->lineEdit_EUR->setText(data[1]);
    ui->lineEdit_Wer->setText(data[2]);

}

QStringList MainWindow::getData(const QString &html){
    QStringList list;

        // Извлекаем курс евро
        QRegularExpression euroRegexp(R"(EUR","rate":([\d\.]+))");
        QRegularExpressionMatch match = euroRegexp.match(html);
        if (match.hasMatch()) {
            QString euroPrice = match.captured(1);
            list.append(euroPrice);
        }

        // Извлекаем курс рубля
        QRegularExpression rubleRegexp(R"(USD","rate":([\d\.]+))");
        match = rubleRegexp.match(html);
        if (match.hasMatch()) {
            QString rublePrice = match.captured(1);
            list.append(rublePrice);
        }

        // Извлекаем погоду
        QRegularExpression weatherRegexp("now\":\\{\"temp\":\"([+-]\\d+)\"");
        match = weatherRegexp.match(html);
        if (match.hasMatch()) {
            QString temperature = match.captured(1);
            list.append(temperature);
        }

        return list;

}

