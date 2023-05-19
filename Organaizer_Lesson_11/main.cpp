#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "taskmodel.h"
#include <QObject>
#include <QWidget>
#include <QSqlTableModel>
#include <QVariantList>
#include "mainwindow.h"



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks.db");

    if(!db.open()){
        qWarning() << "Failed to open database: " << db.lastError().text();
        return -1;
    }

    QString createTableQuery = "CREATE TABLE IF NOT EXISTS tasks (Task TEXT, Deadline TEXT, Progress INTEGER);";
    QSqlQuery createTableSql(db);

    if(!createTableSql.exec(createTableQuery)){
        qWarning() << "Failed to create table:" << createTableSql.lastError().text();
        return -1;
    }

    QList<Task> tasks;
        QString selectQuery = "SELECT * FROM tasks;";
        QSqlQuery selectSql(db);
        if (selectSql.exec(selectQuery)) {
            while (selectSql.next()) {
                Task task;
                task.title = selectSql.value("Task").toString();
                task.deadline = QDate::fromString(selectSql.value("Deadline").toString(), "d.MM.yyyy");
                task.progress = selectSql.value("Progress").toInt();
                tasks.append(task);
            }
        } else {
            qWarning() << "Failed to fetch tasks:" << selectSql.lastError().text();
            return -1;
        }





    TaskModel taskModel;
    taskModel.setTasks(tasks);
    taskModel.setCount(tasks.count());

    MainWindow mainWindow;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("taskModel", &taskModel);
    engine.rootContext()->setContextProperty("mainWindow", &mainWindow);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qmlRegisterType<TaskModel>("TaskModel", 1, 0, "TaskModel");
    qmlRegisterType<MainWindow>("MainWindow", 1, 0, "MainWindow");




    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    /*QObject::connect(&app, &QGuiApplication::aboutToQuit, [&]() {

        QSqlQuery deleteQuery(db);
                if (!deleteQuery.exec("DELETE FROM tasks")) {
                    qWarning() << "Failed to delete tasks:" << deleteQuery.lastError().text();
                }
                QSqlQuery insertQuery(db);
                insertQuery.prepare("INSERT INTO tasks (Task, Deadline, Progress) VALUES (:Task, :Deadline, :Progress);");
                for (const Task& task : taskModel.tasks()) {
                    insertQuery.bindValue(":Task", task.title);
                    insertQuery.bindValue(":Deadline", task.deadline.toString("d.MM.yyyy"));
                    insertQuery.bindValue(":Progress", task.progress);
                    if (!insertQuery.exec()) {
                        qWarning() << "Failed to insert task:" << insertQuery.lastError().text();
                    }
                }

    });*/

    return app.exec();
}
