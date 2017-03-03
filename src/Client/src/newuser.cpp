#include "newuser.h"
#include "ui_newuser.h"
#include <QDir>
#include "keyhash.h"
#include <QMessageBox>
#include "ssl-client.h"
#include <iostream>
#include <string>
#include "variables.h"
#include "dropbox2.h"
#include "time_handle.h"

using namespace std;


newuser::newuser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newuser)
{
    ui->setupUi(this);
}

newuser::~newuser()
{
    delete ui;
}

void newuser::on_signupbutton_clicked()
{

    if(validate_username(ui->newusername->text().toStdString()))
    {
        QMessageBox::information(this,"Error","Invalid Userid/Password");
        return;
    }

    if(ui->newpassword->text() != ui->confirmnewpassword->text())
    {
        QMessageBox::information(this,"Error","Password didnot match");
        return;
    }
    string encrypted_password = keyencrypt(ui->newpassword->text().toStdString());

    int res;
    if((res=send_username(ui->newusername->text().toStdString())) > 0)
    {	

    	#ifdef DEBUG
        cout << res << "SEND USERNAME RETURNED THIS" << endl;
        #endif
        
        QMessageBox::information(this,"Error","Username already taken");
        return;
    }
    else
    {
        send_credentials(ui->newusername->text().toStdString(),encrypted_password);
        QMessageBox::information(this,"info","Account has been created");
    }

    QString filepath(getenv("HOME"));
    filepath += "/Desktop/"+ui->newusername->text();

    QString temp_folder = filepath + "_temp";

    QDir mdir;

    mdir.mkpath(filepath);

    mdir.mkpath(temp_folder);

    temp_folder = temp_folder + "/client_time.txt";
    write_time(temp_folder.toStdString(),0);

    current_username = ui->newusername->text();

    //newhome = new homepage(this);
    this->close();
    main_object->show();
}
