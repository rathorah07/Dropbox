#include "upload.h"
#include "ui_upload.h"
#include <QFileSystemModel>

upload::upload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::upload)
{
    ui->setupUi(this);

    QString path(getenv("HOME"));
    dirmodel =  new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(path);


    ui->treeView->setModel(dirmodel);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(path);

    ui->listView->setModel(filemodel);

}

upload::~upload()
{
    delete ui;
}

void upload::on_treeView_clicked(const QModelIndex &index)
{
    QString path = filemodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(path));
}
