#include "login.h"
#include "ui_login.h"

Login::Login(Driver_Client *driver_clie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    DC = driver_clie;
    QPalette pallet;
    pallet.setBrush(this->backgroundRole() , QBrush(QImage("/home/eileen/Documents/AP/Project/Phase 3/end.JPG")));
    this->setPalette(pallet);
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    std::string username = MainWindow :: qstringtostring(ui->lnUsername->text());
    std::string password = MainWindow :: qstringtostring(ui->lnPassword->text());
    DC->set_key("login " + username +" " +password);
    if(username.size()==0 || password.size()==0)
    {
        MainWindow :: show_exception_message(MainWindow :: stringtoqstring("Please Fill All Boxes!"));
        return;
    }
    std::string temp = DC->check_command("login " + username +" " +password);
    if(temp == "Wrong Username Or Password\n")
    {
        MainWindow :: show_exception_message(MainWindow :: stringtoqstring(temp));
        return;
    }
    else
    {
        this->hide();
//        Account* ac = new Account(DC);
//        ac->show();
    }
}

void Login::on_btnRegister_clicked()
{
    this->hide();
    Register* re = new Register(DC);
    re->show();
}

void Login::on_btnBack_clicked()
{
    this->hide();
    MainWindow* mw = new MainWindow();
    mw->show();
}
