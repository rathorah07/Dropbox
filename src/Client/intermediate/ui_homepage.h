/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_homepage
{
public:
    QAction *ActionUpload;
    QAction *actionNewFolder;
    QAction *actionShare;
    QAction *actionDelete;
    QAction *actionSync;
    QAction *actionLogout;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QToolBar *toolBar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *homepage)
    {
        if (homepage->objectName().isEmpty())
            homepage->setObjectName(QStringLiteral("homepage"));
        homepage->resize(748, 321);
        homepage->setMouseTracking(true);
        ActionUpload = new QAction(homepage);
        ActionUpload->setObjectName(QStringLiteral("ActionUpload"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/upload-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        ActionUpload->setIcon(icon);
        actionNewFolder = new QAction(homepage);
        actionNewFolder->setObjectName(QStringLiteral("actionNewFolder"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/Actions-folder-new-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewFolder->setIcon(icon1);
        actionShare = new QAction(homepage);
        actionShare->setObjectName(QStringLiteral("actionShare"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/Share-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShare->setIcon(icon2);
        actionDelete = new QAction(homepage);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/Recycle-Bin-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon3);
        actionSync = new QAction(homepage);
        actionSync->setObjectName(QStringLiteral("actionSync"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/cloud_sync_weather-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSync->setIcon(icon4);
        actionLogout = new QAction(homepage);
        actionLogout->setObjectName(QStringLiteral("actionLogout"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Images/gnome_panel_force_quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLogout->setIcon(icon5);
        centralwidget = new QWidget(homepage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout->addWidget(treeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        homepage->setCentralWidget(centralwidget);
        toolBar = new QToolBar(homepage);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        homepage->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(homepage);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 748, 23));
        homepage->setMenuBar(menubar);

        toolBar->addAction(ActionUpload);
        toolBar->addAction(actionNewFolder);
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionShare);
        toolBar->addAction(actionSync);
        toolBar->addAction(actionLogout);

        retranslateUi(homepage);

        QMetaObject::connectSlotsByName(homepage);
    } // setupUi

    void retranslateUi(QMainWindow *homepage)
    {
        homepage->setWindowTitle(QApplication::translate("homepage", "MainWindow", 0));
        ActionUpload->setText(QApplication::translate("homepage", "Upload", 0));
        actionNewFolder->setText(QApplication::translate("homepage", "New Folder", 0));
        actionShare->setText(QApplication::translate("homepage", "Share ", 0));
        actionDelete->setText(QApplication::translate("homepage", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("homepage", "Delete", 0));
#endif // QT_NO_TOOLTIP
        actionSync->setText(QApplication::translate("homepage", "sync", 0));
#ifndef QT_NO_TOOLTIP
        actionSync->setToolTip(QApplication::translate("homepage", "sync", 0));
#endif // QT_NO_TOOLTIP
        actionLogout->setText(QApplication::translate("homepage", "logout", 0));
#ifndef QT_NO_TOOLTIP
        actionLogout->setToolTip(QApplication::translate("homepage", "logout", 0));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("homepage", "SHared_with_me", 0));
        pushButton_2->setText(QApplication::translate("homepage", "Server_files", 0));
        toolBar->setWindowTitle(QApplication::translate("homepage", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class homepage: public Ui_homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
