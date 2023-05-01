#ifndef FSYSV_H
#define FSYSV_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDir>

class FSYSV : public QWidget
{
    Q_OBJECT
public:
    explicit FSYSV(QWidget *parent = nullptr);

signals:

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_lineEdit_returnPressed();
private:
    QFileSystemModel *m_model;
    QTreeView *m_treeView;
    QLineEdit *m_lineEdit;

    void setupUI();

};

#endif // FSYSV_H
