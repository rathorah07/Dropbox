#ifndef DROPBOX2_H
#define DROPBOX2_H

#include <QMainWindow>
#include <QObject>
#include <iostream>
#include "homepage.h"
#include "newuser.h"

namespace Ui {
class dropbox2;
}

class dropbox2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit dropbox2(QWidget *parent = 0);
    ~dropbox2();
    homepage *home;
    newuser *newclient;

private slots:
    void on_buttonlogin_clicked();

    void on_signupscreenbutton_clicked();

private:
    Ui::dropbox2 *ui;
   // homepage * home;
   // newuser  *newclient;
};

#endif // DROPBOX2_H
