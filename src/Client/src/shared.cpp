#include "shared.h"
#include "ui_shared.h"
#include <QTableView>
#include <QDebug>
#include "variables.h"
#include "stringobject.h"
#include "ssl-client.h"

vector<stringobject> shared_file;

Shared::Shared(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Shared)
{
    ui->setupUi(this);

}

Shared::~Shared()
{
    delete ui;
}



void Shared::on_actionDownload_triggered()
{

    int pos = ui->listView->currentIndex().row();
    calldownload(shared_file[pos].path,shared_file[pos].owner);

}


void Shared::refresh(){

   shared_file.clear();
   shared_file = sharedwithme(current_username.toStdString());
   model = new QStringListModel(this);
   QStringList filelist;
   QString filename;

   for(int i = 0;i<shared_file.size();i++)
   {
       filename = QString::fromStdString(shared_file[i].name);
       filelist.append(filename);
   }

   model->setStringList(filelist);
   filelist.clear();
   ui->listView->setModel(model);
}
