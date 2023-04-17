#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "parsetext.h"

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


void MainWindow::on_plainTextEdit_textChanged()
{
    QString txt = ui->plainTextEdit->toPlainText();

    qint32 pos = 0;

    while (1) {
        qint32 fnd = txt.indexOf("#@", pos);
        if (fnd == -1) return;
        pos = fnd + 2;
        int r = txt.indexOf("@", pos); //ghg #@RUS@
        int space = txt.indexOf(" ", pos);
        if ((r<space || space == -1) && r != -1){
            ParseText parseText(txt.mid(pos,r-pos));
            QString anw = parseText.parse();
            txt.remove(fnd, r-fnd+1);
            txt.insert(fnd, anw);
            ui->plainTextEdit->setPlainText(txt);
            QTextCursor cursor = ui->plainTextEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->plainTextEdit->setTextCursor(cursor);
        }
    }
}

