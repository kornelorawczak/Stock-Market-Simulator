#include "startmenu.h"
#include "./ui_startmenu.h"
#include "deposit.h"
#include "withdrawal.h"
#include "history.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , balance(1000.0) //start account balance
{
    ui->setupUi(this);

    //timer setup for date and time
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartMenu::updateDateTime);
    timer->start(1000);

    ui->instrumentsButton->setStyleSheet("QPushButton { color: green; font-size: 22px; }"); //uzywanie css dla obiektu

    QStackedWidget* historyWidget = findChild<QStackedWidget*>("historyWidget");
    History* historyWidgetObject = new History();
    historyWidget->addWidget(historyWidgetObject);

    updateBalanceDisplay();

    connect(ui->depositButton, &QPushButton::clicked, this, &StartMenu::showDepositDialog);
    connect(ui->withdrawalButton, &QPushButton::clicked, this, &StartMenu::showWithdrawalDialog);
    connect(ui->historyButton, &QPushButton::clicked, [historyWidget, historyWidgetObject]() {
        historyWidget->setCurrentWidget(historyWidgetObject);
    });
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
    emit balanceChanged(balance);
    updateBalanceDisplay();
}

void StartMenu::subtractWithdrawalAmount(double amount)
{
    balance -= amount;
    emit balanceChanged(balance);
    updateBalanceDisplay();
}

void StartMenu::updateBalanceDisplay()
{
    ui->balanceValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->balanceValue->setText(QString::number(balance, 'f', 2));
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
