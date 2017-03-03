/********************************************************************************
** Form generated from reading UI file 'upload.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOAD_H
#define UI_UPLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_upload
{
public:
    QPushButton *uploadbutton;
    QPushButton *cancelbutton;
    QTreeView *treeView;
    QListView *listView;

    void setupUi(QDialog *upload)
    {
        if (upload->objectName().isEmpty())
            upload->setObjectName(QStringLiteral("upload"));
        upload->resize(760, 355);
        uploadbutton = new QPushButton(upload);
        uploadbutton->setObjectName(QStringLiteral("uploadbutton"));
        uploadbutton->setGeometry(QRect(476, 310, 61, 26));
        cancelbutton = new QPushButton(upload);
        cancelbutton->setObjectName(QStringLiteral("cancelbutton"));
        cancelbutton->setGeometry(QRect(396, 310, 61, 26));
        treeView = new QTreeView(upload);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(0, 0, 491, 301));
        listView = new QListView(upload);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(490, 0, 256, 301));

        retranslateUi(upload);

        QMetaObject::connectSlotsByName(upload);
    } // setupUi

    void retranslateUi(QDialog *upload)
    {
        upload->setWindowTitle(QApplication::translate("upload", "Dialog", 0));
        uploadbutton->setText(QApplication::translate("upload", "open", 0));
        cancelbutton->setText(QApplication::translate("upload", "cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class upload: public Ui_upload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOAD_H
