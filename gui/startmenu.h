#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartMenu;
}
QT_END_NAMESPACE

class StartMenu : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(double balance READ getBalance WRITE setBalance NOTIFY balanceChanged)

public:
    StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

    double getBalance() const { return balance; }
    void setBalance(double newBalance);

signals:
    void balanceChanged(double newBalance);

private:
    Ui::StartMenu *ui;
    double balance;

    void updateBalanceDisplay();
};
#endif // STARTMENU_H
