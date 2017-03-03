/********************************************************************************
** Form generated from reading UI file 'newuser.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSER_H
#define UI_NEWUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newuser
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *newusername;
    QLineEdit *newpassword;
    QLineEdit *confirmnewpassword;
    QPushButton *signupbutton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *newuser)
    {
        if (newuser->objectName().isEmpty())
            newuser->setObjectName(QStringLiteral("newuser"));
        newuser->resize(575, 297);
        centralwidget = new QWidget(newuser);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 60, 81, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 100, 81, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 140, 71, 17));
        newusername = new QLineEdit(centralwidget);
        newusername->setObjectName(QStringLiteral("newusername"));
        newusername->setGeometry(QRect(230, 60, 171, 27));
        newpassword = new QLineEdit(centralwidget);
        newpassword->setObjectName(QStringLiteral("newpassword"));
        newpassword->setGeometry(QRect(230, 100, 171, 27));
        newpassword->setEchoMode(QLineEdit::Password);
        confirmnewpassword = new QLineEdit(centralwidget);
        confirmnewpassword->setObjectName(QStringLiteral("confirmnewpassword"));
        confirmnewpassword->setGeometry(QRect(230, 140, 171, 27));
        confirmnewpassword->setEchoMode(QLineEdit::Password);
        signupbutton = new QPushButton(centralwidget);
        signupbutton->setObjectName(QStringLiteral("signupbutton"));
        signupbutton->setGeometry(QRect(280, 180, 61, 26));
        signupbutton->setAutoDefault(true);
        signupbutton->setFlat(false);
        newuser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(newuser);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 575, 23));
        newuser->setMenuBar(menubar);
        statusbar = new QStatusBar(newuser);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        newuser->setStatusBar(statusbar);

        retranslateUi(newuser);

        signupbutton->setDefault(false);


        QMetaObject::connectSlotsByName(newuser);
    } // setupUi

    void retranslateUi(QMainWindow *newuser)
    {
        newuser->setWindowTitle(QApplication::translate("newuser", "MainWindow", 0));
        label->setText(QApplication::translate("newuser", "Username :", 0));
        label_2->setText(QApplication::translate("newuser", "Password :", 0));
        label_3->setText(QApplication::translate("newuser", "Confirm :", 0));
        signupbutton->setText(QApplication::translate("newuser", "Sign Up", 0));
    } // retranslateUi

};

namespace Ui {
    class newuser: public Ui_newuser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSER_H
