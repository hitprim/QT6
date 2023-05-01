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
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_Open->setText(tr("Open"));
    ui->pushButton_ref->setText(tr("FAQ"));
    ui->pushButton_Save->setText(tr("Save"));
    ui->Read_only->setText(tr("Read only"));
    ui->pushButton_NewFile->setText(tr("New File"));

    filter = tr("Text file(*.txt)");

    QAction *engAction = new QAction(tr("English"), this);
    QAction *ruAction = new QAction(tr("Russian"), this);

    QAction *dark = new QAction(tr("Dark Theme"));
    QAction *light = new QAction(tr("Light Theme"));

    QToolButton *button = ui->toolButton;
    button->setText(tr("Language"));

    QMenu *menu = new QMenu(this);
    menu->addAction(engAction);
    menu->addAction(ruAction);
    button->setMenu(menu);
    button->setPopupMode(QToolButton::InstantPopup);

    QMenu *themeMenu = new QMenu(tr("Themes") ,this);
    themeMenu->addAction(dark);
    themeMenu->addAction(light);
    menuBar()->addMenu(themeMenu);

    QShortcut *openShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);
    QShortcut *saveShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    QShortcut *newShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this);
    QShortcut *quitShort = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this);

    connect(quitShort, SIGNAL(activated()), this, SLOT(quit()));
    connect(openShort, SIGNAL(activated()), this, SLOT(on_pushButton_Open_clicked()));
    connect(saveShort, SIGNAL(activated()), this, SLOT(on_pushButton_Save_clicked()));
    connect(newShort, SIGNAL(activated()), this, SLOT(on_pushButton_NewFile_clicked()));

    connect(engAction, SIGNAL(triggered(bool)), this, SLOT(changeToEng()));
    connect(ruAction, SIGNAL(triggered(bool)), this, SLOT(changeToRus()));

    connect(dark, SIGNAL(triggered(bool)), this, SLOT(setTheme()));
    connect(light, SIGNAL(triggered(bool)), this, SLOT(setTheme()));
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

void MainWindow::setTheme()
{
    QString butName = ((QAction*) sender())->text();
    if(butName == "Dark Theme"){
        qApp->setStyleSheet("QAction { background-color: black; color: white }"
                      "QMainWindow { background-color: black; color: white }"
                      "QPushButton { background-color: black; color: white }"
                      "QToolButton { background-color: black; color: white }"
                      "QTextEdit { background-color: black; color: white }"
                            "QPushButton:hover { background-color: green; color: white }"
                            "QToolButton:hover { background-color: green; color: white }");
    }
    else if(butName == "Light Theme"){
        qApp->setStyleSheet("");
    }
}


void MainWindow::changeToRus()
{
    QApplication::removeTranslator(&translator);
    if (!translator.load(":/tr/QtLanguage_ru.qm")) {
        qWarning() << "Failed to load translation file";
    }
    QApplication::installTranslator(&translator);
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

void MainWindow::on_pushButton_clicked()
{
    viewer.setWindowTitle("File System");
    viewer.setMinimumSize(500, 500);
    viewer.show();
}


void MainWindow::on_pushButton_Print_clicked()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print File");
    if(dlg.exec() != QDialog::Accepted){
        return;
    }
    ui->textEdit->print(&printer);
}

