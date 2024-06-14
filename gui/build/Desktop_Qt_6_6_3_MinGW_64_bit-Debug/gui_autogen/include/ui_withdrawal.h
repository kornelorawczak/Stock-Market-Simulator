/********************************************************************************
** Form generated from reading UI file 'withdrawal.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WITHDRAWAL_H
#define UI_WITHDRAWAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_withdrawal
{
public:
    QPushButton *withdrawalButton;
    QPushButton *cancelButton;
    QLabel *withdrawalLabel;
    QLineEdit *withdrawalValueText;

    void setupUi(QDialog *withdrawal)
    {
        if (withdrawal->objectName().isEmpty())
            withdrawal->setObjectName("withdrawal");
        withdrawal->resize(400, 300);
        withdrawal->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0)"));
        withdrawalButton = new QPushButton(withdrawal);
        withdrawalButton->setObjectName("withdrawalButton");
        withdrawalButton->setGeometry(QRect(210, 170, 80, 22));
        cancelButton = new QPushButton(withdrawal);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(90, 170, 80, 22));
        withdrawalLabel = new QLabel(withdrawal);
        withdrawalLabel->setObjectName("withdrawalLabel");
        withdrawalLabel->setGeometry(QRect(60, 80, 171, 51));
        withdrawalLabel->setStyleSheet(QString::fromUtf8("QLabel#depoAmountLabel {\n"
"	font-size: 18px\n"
"}"));
        withdrawalValueText = new QLineEdit(withdrawal);
        withdrawalValueText->setObjectName("withdrawalValueText");
        withdrawalValueText->setGeometry(QRect(180, 90, 171, 31));

        retranslateUi(withdrawal);

        QMetaObject::connectSlotsByName(withdrawal);
    } // setupUi

    void retranslateUi(QDialog *withdrawal)
    {
        withdrawal->setWindowTitle(QCoreApplication::translate("withdrawal", "Dialog", nullptr));
        withdrawalButton->setText(QCoreApplication::translate("withdrawal", "withdrawal", nullptr));
        cancelButton->setText(QCoreApplication::translate("withdrawal", "cancel", nullptr));
        withdrawalLabel->setText(QCoreApplication::translate("withdrawal", "withdrawal amount:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class withdrawal: public Ui_withdrawal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WITHDRAWAL_H
