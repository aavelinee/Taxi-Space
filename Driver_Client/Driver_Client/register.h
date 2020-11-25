#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "Driver_Client.h"
#include "mainwindow.h"


namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(Driver_Client* driver_clie, QWidget *parent = 0);
    ~Register();

private slots:
    void on_btnRegister_clicked();

    void on_btnBack_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Register *ui;
    Driver_Client* DC;
    bool is_VIP;
};

#endif // REGISTER_H
