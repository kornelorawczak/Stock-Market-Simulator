#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
#include "data.h"

namespace Ui {
class details;
}

class details : public QDialog
{
    Q_OBJECT

public:
    explicit details(QWidget *parent = nullptr);
    ~details();
    void updateDetails(const QString &instrumentName);

signals:
    void balanceUpdated();

private slots:
    void onBuyButtonClicked();
    void onSellButtonClicked();

private:
    Ui::details *ui;
    Data* instrumentObject;
    void loadChartData(const QString &chartFilePath);
    void loadIndicators(const QString &chartFilePath);
};

#endif // DETAILS_H
