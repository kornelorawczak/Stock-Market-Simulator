#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <QDialog>
#include <QTableWidget>

class Portfolio : public QDialog
{
    Q_OBJECT

public:
    explicit Portfolio(QWidget *parent = nullptr);
    ~Portfolio();
    void loadPortfolio(const QString &filePath);

private:
    QTableWidget *portfolioTable;

    void setupTable();
    void setDarkTheme();
    void populateTable(const QStringList &data);
};

#endif // PORTFOLIO_H
