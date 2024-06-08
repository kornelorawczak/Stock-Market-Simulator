#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QCoreApplication>

namespace Ui {
class History;
}

class History : public QDialog
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = nullptr);
    ~History();

    void loadCSVData(const QString &filepath);
private:
    Ui::History *ui;
};

#endif // HISTORY_H
