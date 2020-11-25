#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Driver_Client.h"
#include "login.h"
#include "ss.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static std::string qstringtostring(QString qs);
    static QString stringtoqstring(std::string str);
    static void show_exception_message(QString message);
    ~MainWindow();

private slots:
    void on_btnWelcome_clicked();

private:
    Ui::MainWindow *ui;
    Driver_Client* DC;
};

#endif // MAINWINDOW_H
