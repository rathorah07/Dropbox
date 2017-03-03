#ifndef NEWUSER_H
#define NEWUSER_H

#include <QMainWindow>
#include "homepage.h"

namespace Ui {
class newuser;
}

class newuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit newuser(QWidget *parent = 0);
    ~newuser();

private slots:
    void on_signupbutton_clicked();

private:
    Ui::newuser *ui;
    homepage *newhome;
};

#endif // NEWUSER_H
