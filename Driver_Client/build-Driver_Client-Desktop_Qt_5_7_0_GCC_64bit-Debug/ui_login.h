/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLineEdit *lnUsername;
    QLineEdit *lnPassword;
    QPushButton *btnLogin;
    QLabel *lblNotRegistered;
    QPushButton *btnRegister;
    QPushButton *btnBack;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(605, 970);
        lnUsername = new QLineEdit(Login);
        lnUsername->setObjectName(QStringLiteral("lnUsername"));
        lnUsername->setGeometry(QRect(230, 155, 160, 50));
        lnPassword = new QLineEdit(Login);
        lnPassword->setObjectName(QStringLiteral("lnPassword"));
        lnPassword->setGeometry(QRect(230, 220, 160, 50));
        btnLogin = new QPushButton(Login);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(260, 750, 120, 50));
        lblNotRegistered = new QLabel(Login);
        lblNotRegistered->setObjectName(QStringLiteral("lblNotRegistered"));
        lblNotRegistered->setGeometry(QRect(99, 880, 141, 31));
        btnRegister = new QPushButton(Login);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setGeometry(QRect(240, 880, 100, 30));
        btnBack = new QPushButton(Login);
        btnBack->setObjectName(QStringLiteral("btnBack"));
        btnBack->setGeometry(QRect(480, 20, 96, 27));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", 0));
        lnUsername->setPlaceholderText(QApplication::translate("Login", "Username", 0));
        lnPassword->setPlaceholderText(QApplication::translate("Login", "Password", 0));
        btnLogin->setText(QApplication::translate("Login", "Login", 0));
        lblNotRegistered->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" font-weight:600; color:#00ffff;\">Not Registered?</span></p></body></html>", 0));
        btnRegister->setText(QApplication::translate("Login", "Register", 0));
        btnBack->setText(QApplication::translate("Login", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
