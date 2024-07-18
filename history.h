#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QTableWidget>

class History : public QWidget
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = nullptr);
    void loadHistory(const QString &filePath);

private:
    QTableWidget *historyTable;

    void setupTable();
    void setDarkTheme();
    void populateTable(const QStringList &data);
};

#endif // HISTORY_H
