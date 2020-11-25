/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLineEdit *lnUsername;
    QLineEdit *lnPassword;
    QLineEdit *lnNumber;
    QLineEdit *lnModel;
    QLineEdit *lnYear;
    QLineEdit *lnColor;
    QPushButton *btnRegister;
    QPushButton *btnBack;
    QCheckBox *chckIs_VIP;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QStringLiteral("Register"));
        Register->resize(605, 970);
        lnUsername = new QLineEdit(Register);
        lnUsername->setObjectName(QStringLiteral("lnUsername"));
        lnUsername->setGeometry(QRect(90, 400, 160, 50));
        lnPassword = new QLineEdit(Register);
        lnPassword->setObjectName(QStringLiteral("lnPassword"));
        lnPassword->setGeometry(QRect(90, 470, 160, 50));
        lnNumber = new QLineEdit(Register);
        lnNumber->setObjectName(QStringLiteral("lnNumber"));
        lnNumber->setGeometry(QRect(90, 540, 160, 50));
        lnModel = new QLineEdit(Register);
        lnModel->setObjectName(QStringLiteral("lnModel"));
        lnModel->setGeometry(QRect(360, 400, 160, 50));
        lnYear = new QLineEdit(Register);
        lnYear->setObjectName(QStringLiteral("lnYear"));
        lnYear->setGeometry(QRect(360, 470, 160, 50));
        lnColor = new QLineEdit(Register);
        lnColor->setObjectName(QStringLiteral("lnColor"));
        lnColor->setGeometry(QRect(360, 540, 160, 50));
        btnRegister = new QPushButton(Register);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setGeometry(QRect(250, 760, 120, 50));
        btnBack = new QPushButton(Register);
        btnBack->setObjectName(QStringLiteral("btnBack"));
        btnBack->setGeometry(QRect(40, 900, 96, 27));
        chckIs_VIP = new QCheckBox(Register);
        chckIs_VIP->setObjectName(QStringLiteral("chckIs_VIP"));
        chckIs_VIP->setGeometry(QRect(90, 640, 120, 30));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QApplication::translate("Register", "Form", 0));
        lnUsername->setPlaceholderText(QApplication::translate("Register", "Username", 0));
        lnPassword->setPlaceholderText(QApplication::translate("Register", "Password", 0));
        lnNumber->setPlaceholderText(QApplication::translate("Register", "SpaceShip Number", 0));
        lnModel->setPlaceholderText(QApplication::translate("Register", "SpaceShip Model", 0));
        lnYear->setPlaceholderText(QApplication::translate("Register", "Production Year", 0));
        lnColor->setPlaceholderText(QApplication::translate("Register", "SpaceShip Color", 0));
        btnRegister->setText(QApplication::translate("Register", "Register", 0));
        btnBack->setText(QApplication::translate("Register", "Back", 0));
        chckIs_VIP->setText(QApplication::translate("Register", "VIP", 0));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
