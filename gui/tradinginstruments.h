#ifndef TRADINGINSTRUMENTS_H
#define TRADINGINSTRUMENTS_H

#include <QDialog>

namespace Ui {
class TradingInstruments;
}

class TradingInstruments : public QDialog
{
    Q_OBJECT

public:
    explicit TradingInstruments(QWidget *parent = nullptr);
    ~TradingInstruments();

private:
    Ui::TradingInstruments *ui;
};

#endif // TRADINGINSTRUMENTS_H
