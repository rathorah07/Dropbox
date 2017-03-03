#include "homepage.h"
#include "ui_homepage.h"
#include "variables.h"
#include <QFileDialog>
#include <cstdlib>
#include <pthread.h>
#include <QInputDialog>
#include <string>
#include <QFileInfo>
#include <QDebug>
#include "ssl-client.h"
#include "filehandle.h"
#include "func.h"


bool syncing =true;

using namespace std;
QString pass;

homepage::homepage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homepage)
{

        ui->setupUi(this);
        share_window = new Shared;
        model = new QDirModel(this);
        model->setReadOnly(false);
        model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
        ui->treeView->setModel(model);

        pass=getenv("HOME");
        pass = pass + "/Desktop/"+ current_username;

        QModelIndex index = model->index(pass);
        ui->treeView->setRootIndex(index);
        ui->treeView->expand(index);
        ui->treeView->scrollTo(index);
        ui->treeView->setCurrentIndex(index);
        ui->treeView->resizeColumnToContents(0);

}

homepage::~homepage()
{
    delete ui;
}


void homepage::refresh_homepage(){

    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    ui->treeView->setModel(model);
    QModelIndex index = model->index(pass);
    ui->treeView->setRootIndex(index);
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);
}


void homepage::on_actionNewFolder_triggered()
{
        QModelIndex index = ui->treeView->currentIndex();

        if(!index.isValid())
        {
            return;
        }

        else
        {
            QString name = QInputDialog::getText(this,"New","Enter Folder Name");

            if(name.isEmpty())
            {
                return;
            }

            model->mkdir(index,name);
        }
        refresh_homepage();
}

void homepage::on_ActionUpload_triggered()
{	
    QStringList copy_files = QFileDialog::getOpenFileNames();

    QString current_path = model->filePath(ui->treeView->currentIndex());
    current_path = "'" + current_path +"'";


    string command;

    foreach (QString itm,copy_files) {

        command = "cp " ;
        command =command + "'" + itm.toStdString() + "\'" + " "  + current_path.toStdString();
        system(command.c_str());
       refresh_homepage();
    }
}

void homepage::on_actionDelete_triggered()
{
    QString path = model->filePath(ui->treeView->currentIndex());
    path = "'" + path +"'";

    if(path==pass)
    {
     return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Delete","Yes",QMessageBox::Yes|QMessageBox::No);

    if(reply==QMessageBox::Yes)
    {
         string command;
         command = "rm -r " + path.toStdString();

         system(command.c_str());


    }
    refresh_homepage();

}


void homepage::on_actionSync_triggered()
{

	refresh_homepage();
    string temp_path = "\0";
    temp_path = getenv("HOME");
    temp_path += "/Desktop/" + current_username.toStdString();
    temp_path += "_temp";

    cout<<temp_path<<endl;

    if(!exist_path(temp_path))
    {
       create_dir(temp_path);
    }

    syncing =true;

    

    sleep(1);

    GLOBAL_SYNCHRONIZE(current_username.toStdString(),temp_path);

    syncing =false;

    refresh_homepage();


}


void homepage::on_pushButton_clicked()
{
    refresh_homepage();
    share_window->close();
    share_window->refresh();
    share_window->show();
}

void homepage::on_actionShare_triggered()
{
    QInputDialog ret;
    ret.setLabelText("Share_with");
    ret.exec();
    QString name = ret.textValue();

    if(send_username(name.toStdString())<=0)
    {
        QMessageBox::information(this,"error","User does not exist");
        return;
    }

    QString filepath = model->fileInfo(ui->treeView->currentIndex()).absoluteFilePath();

    filepath = QString::fromStdString(cut_homepath(filepath.toStdString(),getenv("HOME")));

    filepath = QString::fromStdString(cut_homepath(filepath.toStdString(),"/Desktop"));

    string filename = model->fileInfo(ui->treeView->currentIndex()).fileName().toStdString();
    handle_sharing(filename,filepath.toStdString(),current_username.toStdString(),name.toStdString());

    refresh_homepage();
}

void homepage::on_actionLogout_triggered()
{
    this->close();
    main_object->show();
}
