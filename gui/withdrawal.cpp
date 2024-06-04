#include "withdrawal.h"
#include "ui_withdrawal.h"

withdrawal::withdrawal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::withdrawal)
{
    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked, this, &withdrawal::reject);
    connect(ui->withdrawalButton, &QPushButton::clicked, this, &withdrawal::handleWithdrawal);
}

withdrawal::~withdrawal()
{
    delete ui;
}

void withdrawal::handleWithdrawal() {
    double amount = ui->withdrawalValueText->text().toDouble();
    emit withdrawalMade(amount);

    accept();
}
