#ifndef SS_H
#define SS_H

#include <QTabWidget>

namespace Ui {
class ss;
}

class ss : public QTabWidget
{
    Q_OBJECT

public:
    explicit ss(QWidget *parent = 0);
    ~ss();

private:
    Ui::ss *ui;
};

#endif // SS_H
