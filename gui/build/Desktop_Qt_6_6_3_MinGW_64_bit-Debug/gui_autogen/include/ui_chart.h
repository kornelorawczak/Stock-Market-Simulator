/********************************************************************************
** Form generated from reading UI file 'chart.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHART_H
#define UI_CHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chart
{
public:
    QWidget *chartWid;

    void setupUi(QDialog *Chart)
    {
        if (Chart->objectName().isEmpty())
            Chart->setObjectName("Chart");
        Chart->resize(800, 290);
        chartWid = new QWidget(Chart);
        chartWid->setObjectName("chartWid");
        chartWid->setGeometry(QRect(0, 0, 800, 290));

        retranslateUi(Chart);

        QMetaObject::connectSlotsByName(Chart);
    } // setupUi

    void retranslateUi(QDialog *Chart)
    {
        Chart->setWindowTitle(QCoreApplication::translate("Chart", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chart: public Ui_Chart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHART_H
