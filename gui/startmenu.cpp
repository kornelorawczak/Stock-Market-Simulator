#include "startmenu.h"
#include "./ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , balance(1000.0) // balans
{
    ui->setupUi(this);
    ui->instrumentsButton->setStyleSheet("QPushButton { color: green; font-size: 22px; }"); //uzywanie css dla obiektu

    updateBalanceDisplay();
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::setBalance(double newBalance)
{
    if (balance != newBalance) {
        balance = newBalance;
        emit balanceChanged(balance);
        updateBalanceDisplay();
    }
}

void StartMenu::updateBalanceDisplay()
{
    ui->balanceValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->balanceValue->setText(QString::number(balance, 'f', 2));
}
