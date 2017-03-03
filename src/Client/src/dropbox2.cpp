#include "dropbox2.h"
#include "ui_dropbox2.h"
#include <iostream>
#include <QMessageBox>
#include "homepage.h"
#include "newuser.h"
#include <QDir>
#include <string>
#include "keyhash.h"
#include "ssl-client.h"
#include "variables.h"
#include "fileinfo1.h"
#include "time_handle.h"
using namespace std;

QString current_username;

dropbox2::dropbox2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dropbox2)
{
    ui->setupUi(this);

}
dropbox2::~dropbox2()
{
    delete ui;
}

void dropbox2::on_buttonlogin_clicked()
{

   #ifdef DEBUG
   cout<<"Entering login process\n";
   #endif	
   string encrypted_password = keyencrypt(ui->password->text().toStdString());

    
   if(check_credentials(ui->username->text().toStdString(),encrypted_password)!=1)
    {
       QMessageBox::information(this,"Error","Invalid Userid/Password");
       return;
    }

   QString filepath(getenv("HOME"));
   filepath += "/Desktop/"+ui->username->text();

   current_username = ui->username->text();

   QString temp_folder = filepath + "_temp";

   QDir mdir;

   fileinfo stat_object1(filepath.toStdString());
   fileinfo stat_object2(temp_folder.toStdString());

   if(stat_object1.exist==false)
        mdir.mkpath(filepath);

   if(stat_object2.exist==false)
   {
     mdir.mkpath(temp_folder);
     temp_folder = temp_folder + "/client_time.txt";
     write_time(temp_folder.toStdString(),0);
   }


   home = new homepage(this);

   this->close();

   home->show();
}


void dropbox2::on_signupscreenbutton_clicked()
{
    newclient = new newuser(this);

    this->close();

    newclient->show();
}
