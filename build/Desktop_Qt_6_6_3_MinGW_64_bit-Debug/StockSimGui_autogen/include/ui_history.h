/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_History
{
public:
    QTableWidget *historyTable;

    void setupUi(QDialog *History)
    {
        if (History->objectName().isEmpty())
            History->setObjectName("History");
        History->resize(940, 484);
        History->setStyleSheet(QString::fromUtf8(""));
        historyTable = new QTableWidget(History);
        if (historyTable->columnCount() < 6)
            historyTable->setColumnCount(6);
        QFont font;
        font.setPointSize(16);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        historyTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        historyTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        historyTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        historyTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        historyTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        historyTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        historyTable->setObjectName("historyTable");
        historyTable->setGeometry(QRect(0, 0, 941, 491));
        historyTable->setStyleSheet(QString::fromUtf8("QTableWidget#historyTable {\n"
"	border: none;\n"
"}"));

        retranslateUi(History);

        QMetaObject::connectSlotsByName(History);
    } // setupUi

    void retranslateUi(QDialog *History)
    {
        History->setWindowTitle(QCoreApplication::translate("History", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = historyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("History", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = historyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("History", "price", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = historyTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("History", "date", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = historyTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("History", "quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = historyTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("History", "side", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = historyTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("History", "profit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class History: public Ui_History {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
