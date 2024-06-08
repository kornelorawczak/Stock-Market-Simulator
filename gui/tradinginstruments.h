#ifndef TRADINGINSTRUMENTS_H
#define TRADINGINSTRUMENTS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QCoreApplication>

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

    void loadCSVData(const QString &filepath);
};

#endif // TRADINGINSTRUMENTS_H
