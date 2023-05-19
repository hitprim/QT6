class WindowManager : public QObject
{
    Q_OBJECT

public slots:
    void openNewWindow()
    {
        QWidget* newWindow = new QWidget;
        newWindow->resize(800, 600); // Установка размеров окна
        newWindow->show();
    }

public:
    // Добавьте виртуальную функцию деструктора
    virtual ~WindowManager() {}
};
