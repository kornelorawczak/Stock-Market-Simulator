#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Deposit)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Deposit::reject);
    connect(ui->depositButton, &QPushButton::clicked, this, &Deposit::handleDeposit);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::handleDeposit() {
    double amount = ui->depositValueText->text().toDouble();
    emit depositMade(amount);

    // Close the dialog
    accept();
}
