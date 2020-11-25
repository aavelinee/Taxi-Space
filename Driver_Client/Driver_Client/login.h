#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Driver_Client.h"
#include "mainwindow.h"
#include "register.h"
#include "account.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(Driver_Client* driver_clie, QWidget *parent = 0);
    ~Login();

private slots:
    void on_btnLogin_clicked();

    void on_btnRegister_clicked();

    void on_btnBack_clicked();

private:
    Ui::Login *ui;
    Driver_Client* DC;
};

#endif // LOGIN_H
