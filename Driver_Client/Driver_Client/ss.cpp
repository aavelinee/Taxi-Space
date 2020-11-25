#include "ss.h"
#include "ui_ss.h"

ss::ss(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ss)
{

    QPalette pallet;
    pallet.setBrush(this->backgroundRole() , QBrush(QImage("/home/eileen/Documents/AP/Project/Phase 3/Passenger_Client/Passenger_Client/as.jpg")));
    this->setPalette(pallet);
    ui->setupUi(this);
}

ss::~ss()
{
    delete ui;
}
