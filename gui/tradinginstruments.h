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

signals:
    void instrumentSelected(const QString &name);

public:
    explicit TradingInstruments(QWidget *parent = nullptr);
    ~TradingInstruments();

private:
    Ui::TradingInstruments *ui;

    void loadCSVData(const QString &filepath);

private slots:
    void onCellClicked(int row, int column);
};

#endif // TRADINGINSTRUMENTS_H
