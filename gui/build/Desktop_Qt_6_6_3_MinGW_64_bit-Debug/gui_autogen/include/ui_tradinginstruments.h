/********************************************************************************
** Form generated from reading UI file 'tradinginstruments.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRADINGINSTRUMENTS_H
#define UI_TRADINGINSTRUMENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_TradingInstruments
{
public:
    QTableWidget *instrumentsTable;

    void setupUi(QDialog *TradingInstruments)
    {
        if (TradingInstruments->objectName().isEmpty())
            TradingInstruments->setObjectName("TradingInstruments");
        TradingInstruments->resize(940, 484);
        TradingInstruments->setStyleSheet(QString::fromUtf8("QDialog#TradingInstruments {\n"
"	border:\n"
"}"));
        instrumentsTable = new QTableWidget(TradingInstruments);
        if (instrumentsTable->columnCount() < 4)
            instrumentsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        instrumentsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        instrumentsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        instrumentsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        instrumentsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        instrumentsTable->setObjectName("instrumentsTable");
        instrumentsTable->setGeometry(QRect(0, 0, 940, 484));
        instrumentsTable->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(TradingInstruments);

        QMetaObject::connectSlotsByName(TradingInstruments);
    } // setupUi

    void retranslateUi(QDialog *TradingInstruments)
    {
        TradingInstruments->setWindowTitle(QCoreApplication::translate("TradingInstruments", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = instrumentsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TradingInstruments", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = instrumentsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TradingInstruments", "quotes", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = instrumentsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TradingInstruments", "change", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = instrumentsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TradingInstruments", "category", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TradingInstruments: public Ui_TradingInstruments {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRADINGINSTRUMENTS_H
