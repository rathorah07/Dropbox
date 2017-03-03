#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QInputDialog>
#include <QDirModel>
#include <QMessageBox>
#include <QDir>
#include "shared.h"


namespace Ui {
class homepage;
}

class homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = 0);

    void refresh_homepage();
    ~homepage();

    Shared * share_window;

private slots:
    void on_actionNewFolder_triggered();

    void on_ActionUpload_triggered();

    void on_actionDelete_triggered();

    void on_actionSync_triggered();

    void on_pushButton_clicked();

    void on_actionShare_triggered();


    void on_actionLogout_triggered();

private:
    Ui::homepage *ui;
    QDirModel *model;
};

#endif // HOMEPAGE_H
