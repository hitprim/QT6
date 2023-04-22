#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QDataStream>
#include <QHash>
#include <QTextBrowser>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filter = tr("Текстовый файл(*.txt)");

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_Save_clicked()
{
    QString s = QFileDialog::getSaveFileName(this, "Save file",
    QDir::current().path() + "/newfile.txt", filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt"); // определяем, есть ли в названии
        // строка ".txt"
        QFile file(s);
        if (file.open(QFile::WriteOnly))
        {

            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
        }
    }

}


void MainWindow::on_pushButton_Open_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "Open file",
    QDir::current().path(), filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            QTextStream stream(&file);
            ui->textEdit->setPlainText(stream.readAll());
        }
    }
}


void MainWindow::on_pushButton_ref_clicked()
{
    QTextBrowser *helpBrowser = new QTextBrowser(this);
    setCentralWidget(helpBrowser);
    helpBrowser->setSource(QUrl("qrc:/refer/reff.txt"));
    centralWidget()->show();
}

