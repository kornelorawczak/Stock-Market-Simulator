#include "startmenu.h"
#include "./ui_startmenu.h"
#include "deposit.h"
#include "withdrawal.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , balance(1000.0) //account balance
{
    ui->setupUi(this);
    ui->instrumentsButton->setStyleSheet("QPushButton { color: green; font-size: 22px; }"); //uzywanie css dla obiektu

    updateBalanceDisplay();

    connect(ui->depositButton, &QPushButton::clicked, this, &StartMenu::showDepositDialog);
    connect(ui->withdrawalButton, &QPushButton::clicked, this, &StartMenu::showWithdrawalDialog);
}

StartMenu::~StartMenu()
{
    delete ui;
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
