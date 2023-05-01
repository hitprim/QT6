#include "fsysv.h"

FSYSV::FSYSV(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
}

void FSYSV::setupUI()
{
        m_model = new QFileSystemModel();
        m_model->setRootPath(QDir::homePath());

        // Создание представления файловой системы
        m_treeView = new QTreeView(this);
        m_treeView->setModel(m_model);
        m_treeView->setRootIndex(m_model->index(QDir::homePath()));
        m_treeView->setHeaderHidden(true);
        m_treeView->setSortingEnabled(true);
        m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        m_treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);

        // Создание строки навигации
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setText(QDir::homePath());
        connect(m_lineEdit,SIGNAL(returnPressed()), this, SLOT(on_lineEdit_returnPressed()));

        // Создание вертикального макета и добавление представления и строки навигации
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(m_lineEdit);
        layout->addWidget(m_treeView);
        setLayout(layout);

        // Подключение слота на клик по элементу представления
        connect(m_treeView, &QTreeView::clicked, this, &FSYSV::on_treeView_clicked);

}

void FSYSV::on_treeView_clicked(const QModelIndex &index)
{
    // Обновление строки навигации при выборе элемента
    QString path = m_model->filePath(index);
    m_lineEdit->setText(path);
}

void FSYSV::on_lineEdit_returnPressed()
{
    // Обновление представления при изменении пути в строке навигации
    QString path = m_lineEdit->text();
    m_treeView->setRootIndex(m_model->index(path));
}
