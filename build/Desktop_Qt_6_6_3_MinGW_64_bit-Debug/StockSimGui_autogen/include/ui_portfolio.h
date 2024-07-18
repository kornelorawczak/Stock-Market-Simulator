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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Portfolio
{
public:
    QTableWidget *portfolioTable;

    void setupUi(QDialog *Portfolio)
    {
        if (Portfolio->objectName().isEmpty())
            Portfolio->setObjectName("Portfolio");
        Portfolio->resize(940, 484);
        portfolioTable = new QTableWidget(Portfolio);
        if (portfolioTable->columnCount() < 2)
            portfolioTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        portfolioTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        portfolioTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        portfolioTable->setObjectName("portfolioTable");
        portfolioTable->setGeometry(QRect(0, 0, 940, 484));

        retranslateUi(Portfolio);

        QMetaObject::connectSlotsByName(Portfolio);
    } // setupUi

    void retranslateUi(QDialog *Portfolio)
    {
        Portfolio->setWindowTitle(QCoreApplication::translate("Portfolio", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = portfolioTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Portfolio", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = portfolioTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Portfolio", "Quantity", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Portfolio: public Ui_Portfolio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTFOLIO_H
