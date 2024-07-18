/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *mainWin;
    QFrame *funds;
    QLabel *fundsLabel;
    QLabel *AllocatedFundsLabel;
    QLabel *allocatedFundsValue;
    QLabel *freeFundsValue;
    QFrame *instrumentsFrame;
    QPushButton *instrumentsButton;
    QFrame *balance;
    QLabel *balanceLabel;
    QLabel *balanceValue;
    QFrame *information;
    QLabel *dateLabel;
    QLabel *refreshLabel;
    QLabel *marketStatusLabel;
    QLabel *dateTimeLabel;
    QLabel *marketStatusValue;
    QPushButton *refreshValue;
    QFrame *portfolio;
    QPushButton *portfolioButton;
    QFrame *history;
    QPushButton *historyButton;
    QFrame *deposit;
    QPushButton *depositButton;
    QFrame *withdrawal;
    QPushButton *withdrawalButton;
    QStackedWidget *historyWidget;
    QWidget *page;
    QWidget *page_2;
    QStackedWidget *tradingInstrumentsWidget;
    QWidget *page_3;
    QWidget *page_4;
    QStackedWidget *portfolioWidget;
    QWidget *page_5;
    QWidget *page_6;
    QStackedWidget *detailsWidget;
    QWidget *page_7;
    QWidget *page_8;

    void setupUi(QMainWindow *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(1200, 593);
        StartMenu->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        mainWin = new QWidget(StartMenu);
        mainWin->setObjectName("mainWin");
        mainWin->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"QWidget#mainWin {\n"
"    border: 2px solid rgb(255, 225, 255);\n"
"}"));
        funds = new QFrame(mainWin);
        funds->setObjectName("funds");
        funds->setGeometry(QRect(880, 0, 321, 110));
        funds->setStyleSheet(QString::fromUtf8("QFrame#funds {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        funds->setFrameShape(QFrame::StyledPanel);
        funds->setFrameShadow(QFrame::Raised);
        fundsLabel = new QLabel(funds);
        fundsLabel->setObjectName("fundsLabel");
        fundsLabel->setGeometry(QRect(30, 50, 101, 41));
        fundsLabel->setStyleSheet(QString::fromUtf8("QLabel#fundsLabel {\n"
"	font-size: 18px;\n"
"}"));
        AllocatedFundsLabel = new QLabel(funds);
        AllocatedFundsLabel->setObjectName("AllocatedFundsLabel");
        AllocatedFundsLabel->setGeometry(QRect(30, 20, 141, 31));
        AllocatedFundsLabel->setStyleSheet(QString::fromUtf8("QLabel#AllocatedFundsLabel {\n"
"	font-size: 18px;\n"
"}"));
        allocatedFundsValue = new QLabel(funds);
        allocatedFundsValue->setObjectName("allocatedFundsValue");
        allocatedFundsValue->setGeometry(QRect(170, 24, 141, 21));
        freeFundsValue = new QLabel(funds);
        freeFundsValue->setObjectName("freeFundsValue");
        freeFundsValue->setGeometry(QRect(130, 58, 171, 21));
        instrumentsFrame = new QFrame(mainWin);
        instrumentsFrame->setObjectName("instrumentsFrame");
        instrumentsFrame->setGeometry(QRect(260, 0, 317, 110));
        instrumentsFrame->setMaximumSize(QSize(951, 16777215));
        instrumentsFrame->setStyleSheet(QString::fromUtf8("QFrame#instrumentsFrame {\n"
"    border: 2px solid rgb(73, 225, 255);\n"
"}"));
        instrumentsFrame->setFrameShape(QFrame::StyledPanel);
        instrumentsFrame->setFrameShadow(QFrame::Raised);
        instrumentsButton = new QPushButton(instrumentsFrame);
        instrumentsButton->setObjectName("instrumentsButton");
        instrumentsButton->setGeometry(QRect(50, 30, 221, 41));
        instrumentsButton->setStyleSheet(QString::fromUtf8("QPushButton#instrumentsButton {\n"
"	border: none;\n"
"	font-size: 24px;\n"
"}"));
        balance = new QFrame(mainWin);
        balance->setObjectName("balance");
        balance->setGeometry(QRect(570, 0, 317, 110));
        balance->setStyleSheet(QString::fromUtf8("QFrame#balance {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        balance->setFrameShape(QFrame::StyledPanel);
        balance->setFrameShadow(QFrame::Raised);
        balanceLabel = new QLabel(balance);
        balanceLabel->setObjectName("balanceLabel");
        balanceLabel->setGeometry(QRect(60, 30, 101, 41));
        balanceLabel->setStyleSheet(QString::fromUtf8("QLabel#balanceLabel {\n"
"	font-size: 24px;\n"
"}"));
        balanceValue = new QLabel(balance);
        balanceValue->setObjectName("balanceValue");
        balanceValue->setGeometry(QRect(150, 40, 141, 20));
        balanceValue->setStyleSheet(QString::fromUtf8(""));
        information = new QFrame(mainWin);
        information->setObjectName("information");
        information->setGeometry(QRect(0, 0, 261, 110));
        information->setStyleSheet(QString::fromUtf8("QFrame#information {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        information->setFrameShape(QFrame::StyledPanel);
        information->setFrameShadow(QFrame::Raised);
        dateLabel = new QLabel(information);
        dateLabel->setObjectName("dateLabel");
        dateLabel->setGeometry(QRect(26, 10, 51, 31));
        dateLabel->setStyleSheet(QString::fromUtf8("QLabel#dateLabel {\n"
"	font-size: 18px;\n"
"}"));
        refreshLabel = new QLabel(information);
        refreshLabel->setObjectName("refreshLabel");
        refreshLabel->setGeometry(QRect(26, 43, 91, 21));
        refreshLabel->setStyleSheet(QString::fromUtf8("QLabel#refreshLabel {\n"
"	font-size: 18px;\n"
"}"));
        marketStatusLabel = new QLabel(information);
        marketStatusLabel->setObjectName("marketStatusLabel");
        marketStatusLabel->setGeometry(QRect(26, 70, 71, 21));
        marketStatusLabel->setStyleSheet(QString::fromUtf8("QLabel#marketStatusLabel {\n"
"	font-size: 18px;\n"
"}"));
        dateTimeLabel = new QLabel(information);
        dateTimeLabel->setObjectName("dateTimeLabel");
        dateTimeLabel->setGeometry(QRect(76, 19, 161, 16));
        dateTimeLabel->setStyleSheet(QString::fromUtf8("QLabel#dateTimeLabel {\n"
"	font-size: 16px;\n"
"}"));
        marketStatusValue = new QLabel(information);
        marketStatusValue->setObjectName("marketStatusValue");
        marketStatusValue->setGeometry(QRect(101, 69, 91, 21));
        refreshValue = new QPushButton(information);
        refreshValue->setObjectName("refreshValue");
        refreshValue->setGeometry(QRect(110, 39, 141, 31));
        portfolio = new QFrame(mainWin);
        portfolio->setObjectName("portfolio");
        portfolio->setGeometry(QRect(0, 109, 261, 122));
        portfolio->setStyleSheet(QString::fromUtf8("QFrame#portfolio {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
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
        history->setStyleSheet(QString::fromUtf8("QFrame#history {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        history->setFrameShape(QFrame::StyledPanel);
        history->setFrameShadow(QFrame::Raised);
        historyButton = new QPushButton(history);
        historyButton->setObjectName("historyButton");
        historyButton->setGeometry(QRect(50, 40, 151, 41));
        historyButton->setStyleSheet(QString::fromUtf8("QPushButton#historyButton {\n"
"	border: none;\n"
"	font-size: 20px;\n"
"}"));
        deposit = new QFrame(mainWin);
        deposit->setObjectName("deposit");
        deposit->setGeometry(QRect(0, 350, 261, 122));
        deposit->setStyleSheet(QString::fromUtf8("QFrame#deposit {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        deposit->setFrameShape(QFrame::StyledPanel);
        deposit->setFrameShadow(QFrame::Raised);
        depositButton = new QPushButton(deposit);
        depositButton->setObjectName("depositButton");
        depositButton->setGeometry(QRect(80, 50, 80, 22));
        depositButton->setStyleSheet(QString::fromUtf8("QPushButton#depositButton {\n"
"	border: none;\n"
"	font-size: 20px;\n"
"}"));
        withdrawal = new QFrame(mainWin);
        withdrawal->setObjectName("withdrawal");
        withdrawal->setGeometry(QRect(0, 470, 261, 123));
        withdrawal->setStyleSheet(QString::fromUtf8("QFrame#withdrawal {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        withdrawal->setFrameShape(QFrame::StyledPanel);
        withdrawal->setFrameShadow(QFrame::Raised);
        withdrawalButton = new QPushButton(withdrawal);
        withdrawalButton->setObjectName("withdrawalButton");
        withdrawalButton->setGeometry(QRect(70, 50, 111, 22));
        withdrawalButton->setStyleSheet(QString::fromUtf8("QPushButton#withdrawalButton {\n"
"	border: none;\n"
"	font-size: 20px;\n"
"}"));
        historyWidget = new QStackedWidget(mainWin);
        historyWidget->setObjectName("historyWidget");
        historyWidget->setGeometry(QRect(260, 109, 940, 484));
        historyWidget->setStyleSheet(QString::fromUtf8("QStackedWidget#historyWidget {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        page = new QWidget();
        page->setObjectName("page");
        historyWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        historyWidget->addWidget(page_2);
        tradingInstrumentsWidget = new QStackedWidget(mainWin);
        tradingInstrumentsWidget->setObjectName("tradingInstrumentsWidget");
        tradingInstrumentsWidget->setGeometry(QRect(260, 109, 940, 484));
        tradingInstrumentsWidget->setStyleSheet(QString::fromUtf8("QStackedWidget#tradingInstrumentsWidget {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        tradingInstrumentsWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        tradingInstrumentsWidget->addWidget(page_4);
        portfolioWidget = new QStackedWidget(mainWin);
        portfolioWidget->setObjectName("portfolioWidget");
        portfolioWidget->setGeometry(QRect(260, 109, 940, 484));
        portfolioWidget->setStyleSheet(QString::fromUtf8("QStackedWidget#portfolioWidget {\n"
"	border: 2px solid rgb(131, 226, 255)\n"
"}"));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        portfolioWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        portfolioWidget->addWidget(page_6);
        detailsWidget = new QStackedWidget(mainWin);
        detailsWidget->setObjectName("detailsWidget");
        detailsWidget->setGeometry(QRect(260, 109, 940, 484));
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        detailsWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        detailsWidget->addWidget(page_8);
        StartMenu->setCentralWidget(mainWin);

        retranslateUi(StartMenu);

        historyWidget->setCurrentIndex(0);
        tradingInstrumentsWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "Stock Simulator", nullptr));
        fundsLabel->setText(QCoreApplication::translate("StartMenu", "Free Funds:", nullptr));
        AllocatedFundsLabel->setText(QCoreApplication::translate("StartMenu", "Allocated Funds:", nullptr));
        allocatedFundsValue->setText(QString());
        freeFundsValue->setText(QString());
        instrumentsButton->setText(QCoreApplication::translate("StartMenu", "trading instruments", nullptr));
        balanceLabel->setText(QCoreApplication::translate("StartMenu", "Balance:", nullptr));
        balanceValue->setText(QString());
        dateLabel->setText(QCoreApplication::translate("StartMenu", "Date: ", nullptr));
        refreshLabel->setText(QCoreApplication::translate("StartMenu", "Refreshed:", nullptr));
        marketStatusLabel->setText(QCoreApplication::translate("StartMenu", "Markets: ", nullptr));
        dateTimeLabel->setText(QString());
        marketStatusValue->setText(QString());
        refreshValue->setText(QString());
        portfolioButton->setText(QCoreApplication::translate("StartMenu", "portfolio", nullptr));
        historyButton->setText(QCoreApplication::translate("StartMenu", "history", nullptr));
        depositButton->setText(QCoreApplication::translate("StartMenu", "deposit", nullptr));
        withdrawalButton->setText(QCoreApplication::translate("StartMenu", "withdrawal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
