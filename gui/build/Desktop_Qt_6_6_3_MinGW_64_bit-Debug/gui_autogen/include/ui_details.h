/********************************************************************************
** Form generated from reading UI file 'details.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAILS_H
#define UI_DETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_details
{
public:
    QPushButton *buyButton;
    QPushButton *sellButton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QLabel *nameLabel;
    QLabel *priceLabel;
    QLabel *label;
    QLabel *price;
    QWidget *chartWidget;

    void setupUi(QDialog *details)
    {
        if (details->objectName().isEmpty())
            details->setObjectName("details");
        details->resize(940, 484);
        buyButton = new QPushButton(details);
        buyButton->setObjectName("buyButton");
        buyButton->setGeometry(QRect(510, 80, 81, 41));
        buyButton->setStyleSheet(QString::fromUtf8("QPushButton#buyButton {\n"
"	color: green;\n"
"	font-size: 20px;\n"
"}"));
        sellButton = new QPushButton(details);
        sellButton->setObjectName("sellButton");
        sellButton->setGeometry(QRect(710, 80, 81, 41));
        sellButton->setStyleSheet(QString::fromUtf8("QPushButton#sellButton {\n"
"	color: red;\n"
"	font-size: 20px;\n"
"}"));
        textEdit = new QTextEdit(details);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(600, 80, 101, 41));
        textEdit->setStyleSheet(QString::fromUtf8(""));
        textEdit_2 = new QTextEdit(details);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(800, 80, 101, 41));
        textEdit_2->setStyleSheet(QString::fromUtf8(""));
        nameLabel = new QLabel(details);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setGeometry(QRect(130, 80, 111, 41));
        nameLabel->setStyleSheet(QString::fromUtf8("QLabel#nameLabel {\n"
"	font-size: 16px\n"
"}"));
        priceLabel = new QLabel(details);
        priceLabel->setObjectName("priceLabel");
        priceLabel->setGeometry(QRect(360, 80, 101, 41));
        priceLabel->setStyleSheet(QString::fromUtf8("QLabel#priceLabel {\n"
"	font-size: 16px\n"
"}"));
        label = new QLabel(details);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 50, 81, 31));
        label->setStyleSheet(QString::fromUtf8("QLabel#label {\n"
"	font-size: 20px\n"
"}"));
        price = new QLabel(details);
        price->setObjectName("price");
        price->setGeometry(QRect(360, 50, 81, 31));
        price->setStyleSheet(QString::fromUtf8("QLabel#price {\n"
"	font-size: 20px\n"
"}"));
        chartWidget = new QWidget(details);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setGeometry(QRect(70, 140, 781, 291));

        retranslateUi(details);

        QMetaObject::connectSlotsByName(details);
    } // setupUi

    void retranslateUi(QDialog *details)
    {
        details->setWindowTitle(QCoreApplication::translate("details", "Dialog", nullptr));
        buyButton->setText(QCoreApplication::translate("details", "BUY", nullptr));
        sellButton->setText(QCoreApplication::translate("details", "SELL", nullptr));
        nameLabel->setText(QString());
        priceLabel->setText(QString());
        label->setText(QCoreApplication::translate("details", "NAME", nullptr));
        price->setText(QCoreApplication::translate("details", "PRICE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class details: public Ui_details {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAILS_H
