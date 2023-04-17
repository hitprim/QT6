#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    model = new QStandardItemModel(this);
    ui->setupUi(this);
    QStringList list{"С++", "C#","Java", "JavaScript", "PHP", "Python"};

    ui->listView->setModel(model);

    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);

    for(const QString &lang : list){
        QString iconPth = "C:\\Progs\\icons\\"+lang+".png";        //.\\icons\\"+lang+".png"; - не получилось так сделать
        QFile iconFile(iconPth);
        QIcon icon;
        icon.addFile(iconPth);

        QStandardItem *item = new QStandardItem(icon, lang);        //почему-то не выводит первую иконку
        item->setEditable(true);
        model->appendRow(item);
        //model->appendRow(new QStandardItem(QIcon("C:\\Progs\\icons\\"+str+".png"), list[i]));
    }

    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::InternalMove);
    ui->listView->setDropIndicatorShown(true);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView->viewport()->setAcceptDrops(true);
    ui->listView->setDropIndicatorShown(true);
    ui->listView->setDefaultDropAction(Qt::MoveAction);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString lang = ui->lineEdit->text();
    QStandardItem *item = new QStandardItem(QIcon(":/icons/unknown.png"), lang);
        item->setEditable(true);
        model->appendRow(item);
}


void MainWindow::on_pushButton_2_clicked()
{
    QModelIndexList indexes = ui->listView->selectionModel()->selectedIndexes();
    for(const QModelIndex &index : indexes){
        model->removeRow(index.row());
    }
}




void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked){
        ui->listView->setViewMode(QListView::IconMode);
    }
    else{
        ui->listView->setViewMode(QListView::ListMode);
    }
}
