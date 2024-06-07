#include "startmenu.h"
#include "./ui_startmenu.h"
#include "deposit.h"
#include "withdrawal.h"
#include "history.h"
#include "tradinginstruments.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , balance(1000.0) //start account balance
    , allocatedFunds(0.0)
    , freeFunds(balance)
{
    ui->setupUi(this);

    //timer setup for date and time
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartMenu::updateDateTime);
    timer->start(1000);

    ui->instrumentsButton->setStyleSheet("QPushButton { color: green; font-size: 22px; }");

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

    connect(ui->historyButton, &QPushButton::clicked, [this, historyWidget, historyWidgetObject, tradingInstrumentsWidget]() {
        tradingInstrumentsWidget->setVisible(false);
        historyWidget->setVisible(true);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: green; font-size: 22px; }");
        historyWidget->setCurrentWidget(historyWidgetObject);
    });

    connect(ui->instrumentsButton, &QPushButton::clicked, [this, tradingInstrumentsWidget, tradingInstrumentsObject, historyWidget]() {
        historyWidget->setVisible(false);
        tradingInstrumentsWidget->setVisible(true);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: green; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        tradingInstrumentsWidget->setCurrentWidget(tradingInstrumentsObject);
    });

    updateBalanceDisplay();
    updateAllocatedFundsDisplay();
    updateFreeFundsDisplay();

    connect(ui->depositButton, &QPushButton::clicked, this, &StartMenu::showDepositDialog);
    connect(ui->withdrawalButton, &QPushButton::clicked, this, &StartMenu::showWithdrawalDialog);
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
