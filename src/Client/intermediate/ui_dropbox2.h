/********************************************************************************
** Form generated from reading UI file 'dropbox2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DROPBOX2_H
#define UI_DROPBOX2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dropbox2
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *user;
    QLineEdit *username;
    QLabel *pass;
    QLineEdit *password;
    QPushButton *buttonlogin;
    QCheckBox *checkBox;
    QPushButton *signupscreenbutton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *dropbox2)
    {
        if (dropbox2->objectName().isEmpty())
            dropbox2->setObjectName(QStringLiteral("dropbox2"));
        dropbox2->setEnabled(true);
        dropbox2->resize(483, 355);
        dropbox2->setMouseTracking(true);
        dropbox2->setAcceptDrops(true);
        dropbox2->setAutoFillBackground(true);
        centralWidget = new QWidget(dropbox2);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 1, 215, 17));
        label->setScaledContents(false);
        user = new QLabel(centralWidget);
        user->setObjectName(QStringLiteral("user"));
        user->setGeometry(QRect(130, 110, 80, 17));
        username = new QLineEdit(centralWidget);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(210, 110, 146, 27));
        username->setContextMenuPolicy(Qt::ActionsContextMenu);
        username->setAutoFillBackground(true);
        username->setDragEnabled(true);
        username->setCursorMoveStyle(Qt::VisualMoveStyle);
        username->setClearButtonEnabled(true);
        pass = new QLabel(centralWidget);
        pass->setObjectName(QStringLiteral("pass"));
        pass->setGeometry(QRect(130, 150, 76, 17));
        password = new QLineEdit(centralWidget);
        password->setObjectName(QStringLiteral("password"));
        password->setEnabled(true);
        password->setGeometry(QRect(210, 150, 146, 27));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(password->sizePolicy().hasHeightForWidth());
        password->setSizePolicy(sizePolicy);
        password->setAutoFillBackground(true);
        password->setEchoMode(QLineEdit::Password);
        password->setReadOnly(false);
        password->setClearButtonEnabled(true);
        buttonlogin = new QPushButton(centralWidget);
        buttonlogin->setObjectName(QStringLiteral("buttonlogin"));
        buttonlogin->setGeometry(QRect(230, 190, 85, 26));
        buttonlogin->setAutoFillBackground(false);
        buttonlogin->setAutoDefault(true);
        buttonlogin->setFlat(false);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(130, 230, 156, 22));
        checkBox->setChecked(true);
        checkBox->setTristate(false);
        signupscreenbutton = new QPushButton(centralWidget);
        signupscreenbutton->setObjectName(QStringLiteral("signupscreenbutton"));
        signupscreenbutton->setGeometry(QRect(380, 0, 51, 21));
        signupscreenbutton->setMouseTracking(true);
        signupscreenbutton->setAcceptDrops(true);
        signupscreenbutton->setAutoFillBackground(true);
        signupscreenbutton->setStyleSheet(QStringLiteral("color: rgb(0, 35, 255);"));
        signupscreenbutton->setAutoDefault(true);
        signupscreenbutton->setFlat(true);
        dropbox2->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(dropbox2);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        dropbox2->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(dropbox2);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        dropbox2->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        user->setBuddy(username);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(username, password);
        QWidget::setTabOrder(password, buttonlogin);
        QWidget::setTabOrder(buttonlogin, checkBox);
        QWidget::setTabOrder(checkBox, signupscreenbutton);

        retranslateUi(dropbox2);

        buttonlogin->setDefault(false);
        signupscreenbutton->setDefault(false);


        QMetaObject::connectSlotsByName(dropbox2);
    } // setupUi

    void retranslateUi(QMainWindow *dropbox2)
    {
        dropbox2->setWindowTitle(QApplication::translate("dropbox2", "dropbox2", 0));
        label->setText(QApplication::translate("dropbox2", "<html><head/><body><p>Don't have a account ? Register </p></body></html>", 0));
        user->setText(QApplication::translate("dropbox2", "Username : ", 0));
        username->setText(QString());
        pass->setText(QApplication::translate("dropbox2", "Password  :", 0));
        password->setText(QString());
        buttonlogin->setText(QApplication::translate("dropbox2", "Sign In", 0));
        checkBox->setText(QApplication::translate("dropbox2", "Keep me logged in", 0));
        signupscreenbutton->setText(QApplication::translate("dropbox2", "Here", 0));
    } // retranslateUi

};

namespace Ui {
    class dropbox2: public Ui_dropbox2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPBOX2_H
