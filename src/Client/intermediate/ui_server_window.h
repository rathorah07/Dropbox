/********************************************************************************
** Form generated from reading UI file 'server_window.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_WINDOW_H
#define UI_SERVER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_server_window
{
public:
    QWidget *centralwidget;
    QTreeView *treeView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *server_window)
    {
        if (server_window->objectName().isEmpty())
            server_window->setObjectName(QStringLiteral("server_window"));
        server_window->resize(800, 600);
        centralwidget = new QWidget(server_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 40, 256, 192));
        server_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(server_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        server_window->setMenuBar(menubar);
        statusbar = new QStatusBar(server_window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        server_window->setStatusBar(statusbar);

        retranslateUi(server_window);

        QMetaObject::connectSlotsByName(server_window);
    } // setupUi

    void retranslateUi(QMainWindow *server_window)
    {
        server_window->setWindowTitle(QApplication::translate("server_window", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class server_window: public Ui_server_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_WINDOW_H
