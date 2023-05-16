#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QDebug>
#include "taskmodel.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QString resFilePath = ":/tasks/tasks.txt";
    QString destFilePath = QCoreApplication::applicationDirPath() + "/tasks.txt";
    QFile::copy(resFilePath, destFilePath);

    QList<Task> tasks;
    QFile file(destFilePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList taskData = line.split(';');
            if (taskData.size() == 3) {
                Task task;
                task.title = taskData[0];
                task.deadline = QDate::fromString(taskData[1], "d.MM.yyyy");
                task.progress = taskData[2].toInt();
                tasks.append(task);
            }

        }
        file.close();
    }

    TaskModel taskModel;
    taskModel.setTasks(tasks);
    taskModel.setCount(tasks.count());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("taskModel", &taskModel);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qmlRegisterType<TaskModel>("TaskModel", 1, 0, "TaskModel");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&]() {
        QFile file(destFilePath);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            for (auto& task : taskModel.tasks()) {
                out << task.title << "; " << task.deadline.toString("d.MM.yyyy") << "; " << task.progress << "\n";
            }
            file.close();
        }
    });

    return app.exec();
}
