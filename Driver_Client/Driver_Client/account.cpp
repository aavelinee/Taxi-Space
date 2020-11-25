#include "account.h"
#include "ui_account.h"

Account::Account(Driver_Client *driver_clie, QWidget *parent) :
    QToolBox(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
    DC = driver_clie;
}

Account::~Account()
{
    delete ui;
}
