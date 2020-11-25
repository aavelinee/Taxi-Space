/********************************************************************************
** Form generated from reading UI file 'ss.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SS_H
#define UI_SS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ss
{
public:
    QWidget *tab;
    QWidget *tab1;

    void setupUi(QTabWidget *ss)
    {
        if (ss->objectName().isEmpty())
            ss->setObjectName(QStringLiteral("ss"));
        ss->resize(666, 461);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        ss->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        ss->addTab(tab1, QString());

        retranslateUi(ss);

        QMetaObject::connectSlotsByName(ss);
    } // setupUi

    void retranslateUi(QTabWidget *ss)
    {
        ss->setWindowTitle(QApplication::translate("ss", "TabWidget", 0));
        ss->setTabText(ss->indexOf(tab), QApplication::translate("ss", "Tab 1", 0));
        ss->setTabText(ss->indexOf(tab1), QApplication::translate("ss", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class ss: public Ui_ss {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SS_H
