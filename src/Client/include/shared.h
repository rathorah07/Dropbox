#ifndef SHARED_H
#define SHARED_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class Shared;
}

class Shared : public QMainWindow
{
    Q_OBJECT

public:
    explicit Shared(QWidget *parent = 0);
    ~Shared();
    QStringListModel *model;
    void refresh();

private slots:
    void on_actionDownload_triggered();


private:
    Ui::Shared *ui;
};

#endif // SHARED_H
