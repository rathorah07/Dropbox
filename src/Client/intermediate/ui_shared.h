/********************************************************************************
** Form generated from reading UI file 'shared.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARED_H
#define UI_SHARED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Shared
{
public:
    QAction *actionDownload;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Shared)
    {
        if (Shared->objectName().isEmpty())
            Shared->setObjectName(QStringLiteral("Shared"));
        Shared->setEnabled(true);
        Shared->resize(385, 352);
        actionDownload = new QAction(Shared);
        actionDownload->setObjectName(QStringLiteral("actionDownload"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Downloads-Folder-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownload->setIcon(icon);
        centralwidget = new QWidget(Shared);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);

        Shared->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Shared);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Shared->setStatusBar(statusbar);
        toolBar = new QToolBar(Shared);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        Shared->addToolBar(Qt::LeftToolBarArea, toolBar);

        toolBar->addAction(actionDownload);

        retranslateUi(Shared);

        QMetaObject::connectSlotsByName(Shared);
    } // setupUi

    void retranslateUi(QMainWindow *Shared)
    {
        Shared->setWindowTitle(QApplication::translate("Shared", "MainWindow", 0));
        actionDownload->setText(QApplication::translate("Shared", "Download", 0));
        toolBar->setWindowTitle(QApplication::translate("Shared", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class Shared: public Ui_Shared {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARED_H
