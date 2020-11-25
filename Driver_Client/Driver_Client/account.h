#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QToolBox>
#include "mainwindow.h"
#include "Driver_Client.h"

namespace Ui {
class Account;
}

class Account : public QToolBox
{
    Q_OBJECT

public:
    explicit Account(Driver_Client* driver_clie, QWidget *parent = 0);
    ~Account();

private:
    Ui::Account *ui;
    Driver_Client* DC;
};

#endif // ACCOUNT_H
