#ifndef TRADINGINSTRUMENTS_H
#define TRADINGINSTRUMENTS_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class TradingInstruments;
}

class TradingInstruments : public QDialog
{
    Q_OBJECT

public:
    explicit TradingInstruments(QWidget *parent = nullptr);
    ~TradingInstruments();
    void loadInstruments(const QString &filePath);

signals:
    void instrumentSelected(const QString &instrumentName);

private slots:
    void onCellClicked(int row, int column);

private:
    Ui::TradingInstruments *ui;
    void setupTable();
    void setDarkTheme();
    void populateTable(const QStringList &data);
};

#endif // TRADINGINSTRUMENTS_H
