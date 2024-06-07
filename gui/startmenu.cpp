#include "startmenu.h"
#include "./ui_startmenu.h"
#include "deposit.h"
#include "withdrawal.h"
#include "history.h"
#include "tradinginstruments.h"
#include "portfolio.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , balance(1000.0) //start account balance
    , allocatedFunds(0.0)
    , freeFunds(balance)
    , currentWeekday(QDate::currentDate().dayOfWeek())
{
    ui->setupUi(this);

    ui->instrumentsButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");

    //timer setup for date and time
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartMenu::updateDateTime);
    timer->start(1000);

    midnightTimer = new QTimer(this);
    connect(midnightTimer, &QTimer::timeout, this, &StartMenu::updateMarketStatus);
    midnightTimer->start(10000);

    if (currentWeekday == 6 || currentWeekday == 7) {
        marketStatus = "closed";
        ui->marketStatusValue->setStyleSheet("QLabel { color: red; font-size: 18px; }");
    } else {
        marketStatus = "open";
        ui->marketStatusValue->setStyleSheet("QLabel { color: lime; font-size: 18px; }");
    }
    ui->marketStatusValue->setText(marketStatus);

    //subpage history
    QStackedWidget* historyWidget = findChild<QStackedWidget*>("historyWidget");
    History* historyWidgetObject = new History();
    historyWidget->addWidget(historyWidgetObject);
    historyWidget->setVisible(false);

    //subpage tradinginstruments
    QStackedWidget* tradingInstrumentsWidget = findChild<QStackedWidget*>("tradingInstrumentsWidget");
    TradingInstruments* tradingInstrumentsObject = new TradingInstruments();
    tradingInstrumentsWidget->addWidget(tradingInstrumentsObject);
    tradingInstrumentsWidget->setVisible(true);

    tradingInstrumentsWidget->setCurrentWidget(tradingInstrumentsObject); //initially trading instruments are mainpage

    QStackedWidget* portfolioWidget = findChild<QStackedWidget*>("portfolioWidget");
    Portfolio* portfolioObject = new Portfolio();
    portfolioWidget->addWidget(portfolioObject);
    portfolioWidget->setVisible(false);

    connect(ui->historyButton, &QPushButton::clicked, [this, historyWidget, historyWidgetObject, tradingInstrumentsWidget, portfolioWidget]() {
        tradingInstrumentsWidget->setVisible(false);
        portfolioWidget->setVisible(false);
        historyWidget->setVisible(true);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
        ui->portfolioButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        historyWidget->setCurrentWidget(historyWidgetObject);
    });

    connect(ui->instrumentsButton, &QPushButton::clicked, [this, tradingInstrumentsWidget, tradingInstrumentsObject, historyWidget, portfolioWidget]() {
        historyWidget->setVisible(false);
        portfolioWidget->setVisible(false);
        tradingInstrumentsWidget->setVisible(true);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->portfolioButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        tradingInstrumentsWidget->setCurrentWidget(tradingInstrumentsObject);
    });

    connect(ui->portfolioButton, &QPushButton::clicked, [this, portfolioWidget, portfolioObject, tradingInstrumentsWidget, historyWidget]() {
        historyWidget->setVisible(false);
        portfolioWidget->setVisible(true);
        tradingInstrumentsWidget->setVisible(false);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->portfolioButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
        portfolioWidget->setCurrentWidget(portfolioObject);
    });

    connect(ui->depositButton, &QPushButton::clicked, this, &StartMenu::showDepositDialog);
    connect(ui->withdrawalButton, &QPushButton::clicked, this, &StartMenu::showWithdrawalDialog);

    updateBalanceDisplay();
    updateAllocatedFundsDisplay();
    updateFreeFundsDisplay();
}

StartMenu::~StartMenu()
{
    delete ui;
    delete timer;
}

void StartMenu::updateDateTime() {
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeText = dateTime.toString("hh:mm:ss dd:MM:yyyy");
    ui->dateTimeLabel->setText(dateTimeText);
}

void StartMenu::updateMarketStatus() {
    int newWeekDay = QDate::currentDate().dayOfWeek();
    if (newWeekDay != currentWeekday) {
        currentWeekday = newWeekDay;
        if (currentWeekday == 6 || currentWeekday == 7) {
            marketStatus = "closed";
            ui->marketStatusValue->setStyleSheet("QLabel { color: red; font-size: 18px; }");
        } else {
            marketStatus = "open";
            ui->marketStatusValue->setStyleSheet("QLabel { color: lime; font-size: 18px; }");
        }
    }
    ui->marketStatusValue->setText(marketStatus);
}

//balance
void StartMenu::addDepositAmount(double amount)
{
    balance += amount;
    freeFunds += amount;
    emit balanceChanged(balance);
    emit freeFundsChanged(freeFunds);
    updateBalanceDisplay();
    updateFreeFundsDisplay();
}

void StartMenu::subtractWithdrawalAmount(double amount)
{
    balance -= amount;
    freeFunds -= amount;
    emit balanceChanged(balance);
    emit freeFundsChanged(freeFunds);
    updateBalanceDisplay();
    updateFreeFundsDisplay();
}

void StartMenu::updateBalanceDisplay()
{
    ui->balanceValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->balanceValue->setText(QString::number(balance, 'f', 2));
}

void StartMenu::updateAllocatedFundsDisplay()
{
    ui->allocatedFundsValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->allocatedFundsValue->setText(QString::number(allocatedFunds, 'f', 2));
}

void StartMenu::updateFreeFundsDisplay()
{
    ui->freeFundsValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->freeFundsValue->setText(QString::number(freeFunds, 'f', 2));
}

//deposit page
void StartMenu::showDepositDialog() {
    Deposit depositDialog(this);
    connect(&depositDialog, &Deposit::depositMade, this, &StartMenu::addDepositAmount);
    depositDialog.exec();
}

void StartMenu::showWithdrawalDialog() {
    withdrawal withdrawalDialog(this);
    connect(&withdrawalDialog, &withdrawal::withdrawalMade, this, &StartMenu::subtractWithdrawalAmount);
    withdrawalDialog.exec();
}
