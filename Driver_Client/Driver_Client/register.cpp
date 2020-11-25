#include "register.h"
#include "ui_register.h"

Register::Register(Driver_Client *driver_clie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    DC = driver_clie;
    QPalette pallet;
    pallet.setBrush(this->backgroundRole() , QBrush(QImage("/home/eileen/Documents/AP/Project/Phase 3/end.JPG")));
    this->setPalette(pallet);
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_btnRegister_clicked()
{
    std::string username = MainWindow :: qstringtostring(ui->lnUsername->text());
    std::string password = MainWindow :: qstringtostring(ui->lnPassword->text());
    std::string spsNumber = MainWindow :: qstringtostring(ui->lnNumber->text());
    std::string spsModel = MainWindow :: qstringtostring(ui->lnModel->text());
    std::string spsYear = MainWindow :: qstringtostring(ui->lnYear->text());
    std::string spsColor = MainWindow :: qstringtostring(ui->lnColor->text());


    DC->set_key("register " + username + " " + password + " " + spsNumber + " " + spsModel + " " + spsYear + " " + spsColor);
    if(username.size()==0 || password.size()==0 || spsNumber.size()==0 || spsModel.size()==0 || spsYear.size()==0 || spsColor.size()==0)
    {
        MainWindow :: show_exception_message(MainWindow :: stringtoqstring("Please Fill All Boxes!"));
        return;
    }
    std::string temp;
    if(is_VIP)
        temp = DC->check_command("register VIP " + username + " " + password + " " + spsNumber + " " + spsModel + " " + spsYear + " " + spsColor);
    else
        temp = DC->check_command("register " + username + " " + password + " " + spsNumber + " " + spsModel + " " + spsYear + " " + spsColor);

    if(temp=="Wrong Username Or Password\n" || temp=="Invalid SpaceShip Number\n" || temp=="Invalid SpaceShip Model\n")
    {
        MainWindow :: show_exception_message(MainWindow :: stringtoqstring(temp));
        return;
    }
    else
    {
        this->hide();
        Login* lg = new Login(DC);
        lg->show();
    }
}


void Register::on_btnBack_clicked()
{
    this->hide();
    Login* lg = new Login(DC);
    lg->show();
}

void Register::on_checkBox_clicked(bool checked)
{
    if(checked)
        is_VIP = true;
    else
        is_VIP = false;
}
