#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(DC == NULL)
        DC = new Driver_Client("127.0.0.1" , "5000");
    this->setStyleSheet("QWidget {background-image: url(/home/eileen/Documents/AP/Project/Phase 3/start.PNG) }");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete DC;
    delete ui;
}

std::string MainWindow :: qstringtostring(QString qs)
{
    std::string utf8_text = qs.toUtf8().constData();
    std::string current_locale_text = qs.toLocal8Bit().constData();
    return current_locale_text;
}

QString MainWindow :: stringtoqstring(std::string str)
{
    QString qstr = QString::fromStdString(str);
    return qstr;
}

void MainWindow::show_exception_message(QString message)
{
     QMessageBox excep;
     excep.setText(message);
     excep.exec();
}

void MainWindow::on_btnWelcome_clicked()
{
    this->hide();
    Login* lg = new Login(DC);
    lg->show();
}
