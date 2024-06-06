#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartMenu;
}
QT_END_NAMESPACE

class StartMenu : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(double balance READ getBalance NOTIFY balanceChanged)

public:
    StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

    double getBalance() const { return balance; }
    void addDepositAmount(double newBalance);
    void subtractWithdrawalAmount(double amount);

signals:
    void balanceChanged(double newBalance);

private:
    Ui::StartMenu *ui;
    double balance;
    QTimer *timer;

    void updateDateTime();
    void updateBalanceDisplay();
    void showDepositDialog();
    void showWithdrawalDialog();
};
#endif // STARTMENU_H