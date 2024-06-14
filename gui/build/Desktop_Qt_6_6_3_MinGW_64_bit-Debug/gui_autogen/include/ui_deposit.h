/********************************************************************************
** Form generated from reading UI file 'deposit.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSIT_H
#define UI_DEPOSIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Deposit
{
public:
    QLabel *depoAmountLabel;
    QLineEdit *depositValueText;
    QPushButton *depositButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Deposit)
    {
        if (Deposit->objectName().isEmpty())
            Deposit->setObjectName("Deposit");
        Deposit->resize(409, 300);
        Deposit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0)"));
        depoAmountLabel = new QLabel(Deposit);
        depoAmountLabel->setObjectName("depoAmountLabel");
        depoAmountLabel->setGeometry(QRect(40, 80, 151, 51));
        depoAmountLabel->setStyleSheet(QString::fromUtf8("QLabel#depoAmountLabel {\n"
"	font-size: 18px\n"
"}"));
        depositValueText = new QLineEdit(Deposit);
        depositValueText->setObjectName("depositValueText");
        depositValueText->setGeometry(QRect(190, 90, 171, 31));
        depositButton = new QPushButton(Deposit);
        depositButton->setObjectName("depositButton");
        depositButton->setGeometry(QRect(210, 170, 80, 22));
        cancelButton = new QPushButton(Deposit);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(100, 170, 80, 22));

        retranslateUi(Deposit);

        QMetaObject::connectSlotsByName(Deposit);
    } // setupUi

    void retranslateUi(QDialog *Deposit)
    {
        Deposit->setWindowTitle(QCoreApplication::translate("Deposit", "Dialog", nullptr));
        depoAmountLabel->setText(QCoreApplication::translate("Deposit", "deposit amount: ", nullptr));
        depositButton->setText(QCoreApplication::translate("Deposit", "deposit", nullptr));
        cancelButton->setText(QCoreApplication::translate("Deposit", "cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Deposit: public Ui_Deposit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSIT_H
