#include "withdrawal.h"
#include "ui_withdrawal.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

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

double withdrawal::loadFreeFunds() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/balance.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open balance file for reading.";
        return 0.0;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    QStringList fields = line.split(' ');

    file.close();

    if (fields.size() >= 1) {
        return fields[0].toDouble();
    }

    return 0.0;
}

void withdrawal::handleWithdrawal() {
    double amount = ui->withdrawalValueText->text().toDouble();
    double freeFunds = loadFreeFunds();

    if (amount > freeFunds) {
        QMessageBox::critical(this, "Error", "You cannot withdraw more than the available free funds.");
        return;
    }

    emit withdrawalMade(amount);
    accept();
}
