#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QDialog>

namespace Ui {
class withdrawal;
}

class withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit withdrawal(QWidget *parent = nullptr);
    ~withdrawal();

signals:
    void withdrawalMade(double amount);

private slots:
    void handleWithdrawal();

private:
    Ui::withdrawal *ui;
    double loadFreeFunds();
};

#endif // WITHDRAWAL_H
