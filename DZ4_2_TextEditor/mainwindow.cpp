#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QDataStream>
#include <QHash>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QApplication>
#include <QToolButton>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //translator.load(":/tr/QtLanguage_"+QLocale::system().name());
    //qApp->installTranslator(&translator);

    ui->pushButton_Open->setText(tr("Open"));
    ui->pushButton_ref->setText(tr("FAQ"));
    ui->pushButton_Save->setText(tr("Save"));
    ui->Read_only->setText(tr("Read only"));
    ui->pushButton_NewFile->setText(tr("New File"));

    filter = tr("Text file(*.txt)");

    QAction *engAction = new QAction(tr("English"), this);
    QAction *ruAction = new QAction(tr("Russian"), this);

    QToolButton *button = ui->toolButton;
    button->setText(tr("Language"));
    button->setPopupMode(QToolButton::InstantPopup);

    QMenu *menu = new QMenu(this);
    menu->addAction(engAction);
    menu->addAction(ruAction);

    button->setMenu(menu);

    button->setPopupMode(QToolButton::InstantPopup);

    //QMenu *langMenu = new QMenu(tr("Language") ,this);
    //langMenu->setFont(font);
    //langMenu->setTitle(tr("Language"));

    //langMenu->addAction(engAction);
    //langMenu->addAction(ruAction);
    //menuBar()->addMenu(langMenu);

    QShortcut *openShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);
    QShortcut *saveShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    QShortcut *newShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this);
    QShortcut *quitShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this);

    connect(quitShort, SIGNAL(activated()), this, SLOT(quit()));
    connect(openShort, SIGNAL(activated()), this, SLOT(on_pushButton_Open_clicked()));

    connect(engAction, SIGNAL(triggered(bool)), this, SLOT(changeToEng()));
    connect(ruAction, SIGNAL(triggered(bool)), this, SLOT(changeToRus()));

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_Save_clicked()
{
    QString s = QFileDialog::getSaveFileName(this, tr("Save file"),
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
    QString s = QFileDialog::getOpenFileName(this, tr("Open file"),
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


void MainWindow::on_Read_only_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, tr("Open file"),
    QDir::current().path(), filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            QTextStream stream(&file);
            ui->textEdit->setPlainText(stream.readAll());
            ui->textEdit->setReadOnly(true);
        }
    }
}


void MainWindow::on_pushButton_NewFile_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::quit()
{
    qApp->quit();
}


void MainWindow::changeToRus()
{
    qApp->removeTranslator(&translator);
    if (!translator.load(":/tr/QtLanguage_ru.qm")) {
        qWarning() << "Failed to load translation file";
    }
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::changeToEng()
{
    qApp->removeTranslator(&translator);
    if (!translator.load(":/tr/QtLanguage_en_US.qm")) {
        qWarning() << "Failed to load translation file";
    }
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}




