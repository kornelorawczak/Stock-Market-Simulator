#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartMenu;
}
QT_END_NAMESPACE

class StartMenu : public QMainWindow
{
    Q_OBJECT

public:
    StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

    void addDepositAmount(double newBalance);
    void subtractWithdrawalAmount(double amount);

public slots:
    void updateRefreshButton();
    void showDetails(const QString &instrumentName);
    void refreshDataAndReloadTable();
    void updateBalanceDisplays();

signals:
    void balanceChanged(double newBalance);
    void allocatedFundsChanged(double amount);
    void freeFundsChanged(double amount);

private:
    Ui::StartMenu *ui;
    double balance;
    QTimer *timer;
    QTimer *midnightTimer;
    int currentWeekday;
    double freeFunds;
    double allocatedFunds;
    QString marketStatus;

    void updateMarketStatus();
    void updateDateTime();
    void updateBalanceDisplay();
    void updateAllocatedFundsDisplay();
    void updateFreeFundsDisplay();
    void showDepositDialog();
    void showWithdrawalDialog();
    void showDetailsWidget(const QString &instrumentName);

    void saveSettingstoCSV();
    void loadSettingsfromCSV();
    void loadBalancefromCSV();
    void saveBalancetoCSV();
    void fetchDataAndWriteToCSV();
};

#endif // STARTMENU_H
