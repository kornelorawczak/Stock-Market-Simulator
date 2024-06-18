#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>

namespace Ui {
class Deposit;
}

class Deposit : public QDialog
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

signals:
    void depositMade(double amount);

private:
    Ui::Deposit *ui;

    void handleDeposit();
};

#endif // DEPOSIT_H
