/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *mainWin;
    QFrame *symbols;
    QFrame *Balance;
    QFrame *allocFunds;
    QFrame *information;
    QFrame *portfolio;
    QPushButton *portfolioButton;
    QFrame *history;
    QFrame *deposit;
    QFrame *withdrawal;

    void setupUi(QMainWindow *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(1200, 593);
        StartMenu->setStyleSheet(QString::fromUtf8("border: 2px solid rgb(131, 226, 255)"));
        mainWin = new QWidget(StartMenu);
        mainWin->setObjectName("mainWin");
        mainWin->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"QWidget#mainWin {\n"
"    border: 2px solid rgb(255, 225, 255);\n"
"}"));
        symbols = new QFrame(mainWin);
        symbols->setObjectName("symbols");
        symbols->setGeometry(QRect(880, 0, 321, 110));
        symbols->setFrameShape(QFrame::StyledPanel);
        symbols->setFrameShadow(QFrame::Raised);
        Balance = new QFrame(mainWin);
        Balance->setObjectName("Balance");
        Balance->setGeometry(QRect(260, 0, 317, 110));
        Balance->setMaximumSize(QSize(951, 16777215));
        Balance->setStyleSheet(QString::fromUtf8("QFrame#Balance {\n"
"    border: 2px solid rgb(73, 225, 255);\n"
"}"));
        Balance->setFrameShape(QFrame::StyledPanel);
        Balance->setFrameShadow(QFrame::Raised);
        allocFunds = new QFrame(mainWin);
        allocFunds->setObjectName("allocFunds");
        allocFunds->setGeometry(QRect(570, 0, 317, 110));
        allocFunds->setFrameShape(QFrame::StyledPanel);
        allocFunds->setFrameShadow(QFrame::Raised);
        information = new QFrame(mainWin);
        information->setObjectName("information");
        information->setGeometry(QRect(0, 0, 261, 110));
        information->setStyleSheet(QString::fromUtf8("color: rgb(73, 225, 255)"));
        information->setFrameShape(QFrame::StyledPanel);
        information->setFrameShadow(QFrame::Raised);
        portfolio = new QFrame(mainWin);
        portfolio->setObjectName("portfolio");
        portfolio->setGeometry(QRect(0, 109, 261, 122));
        portfolio->setFrameShape(QFrame::StyledPanel);
        portfolio->setFrameShadow(QFrame::Raised);
        portfolioButton = new QPushButton(portfolio);
        portfolioButton->setObjectName("portfolioButton");
        portfolioButton->setGeometry(QRect(50, 40, 151, 41));
        portfolioButton->setStyleSheet(QString::fromUtf8("QPushButton#portfolioButton {\n"
"	border: none;\n"
"	font-size: 20px;\n"
"}"));
        history = new QFrame(mainWin);
        history->setObjectName("history");
        history->setGeometry(QRect(0, 230, 261, 123));
        history->setFrameShape(QFrame::StyledPanel);
        history->setFrameShadow(QFrame::Raised);
        deposit = new QFrame(mainWin);
        deposit->setObjectName("deposit");
        deposit->setGeometry(QRect(0, 350, 261, 122));
        deposit->setFrameShape(QFrame::StyledPanel);
        deposit->setFrameShadow(QFrame::Raised);
        withdrawal = new QFrame(mainWin);
        withdrawal->setObjectName("withdrawal");
        withdrawal->setGeometry(QRect(0, 470, 261, 123));
        withdrawal->setFrameShape(QFrame::StyledPanel);
        withdrawal->setFrameShadow(QFrame::Raised);
        StartMenu->setCentralWidget(mainWin);

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "Stock Simulator", nullptr));
        portfolioButton->setText(QCoreApplication::translate("StartMenu", "portfolio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
