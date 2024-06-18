/********************************************************************************
** Form generated from reading UI file 'portfolio.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTFOLIO_H
#define UI_PORTFOLIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Portfolio
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *Portfolio)
    {
        if (Portfolio->objectName().isEmpty())
            Portfolio->setObjectName("Portfolio");
        Portfolio->resize(940, 484);
        pushButton = new QPushButton(Portfolio);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(250, 210, 80, 22));

        retranslateUi(Portfolio);

        QMetaObject::connectSlotsByName(Portfolio);
    } // setupUi

    void retranslateUi(QDialog *Portfolio)
    {
        Portfolio->setWindowTitle(QCoreApplication::translate("Portfolio", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Portfolio", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Portfolio: public Ui_Portfolio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTFOLIO_H
