#ifndef UPLOAD_H
#define UPLOAD_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class upload;
}

class upload : public QDialog
{
    Q_OBJECT

public:
    explicit upload(QWidget *parent = 0);
    ~upload();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::upload *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
};

#endif // UPLOAD_H
