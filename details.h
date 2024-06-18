#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
#include <QTextStream>
#include <QFile>
#include <QFont>
#include <QMessageBox>
#include <QStackedWidget>

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

private:
    Ui::details *ui;
    void loadChartData(const QString &chartFilePath);
};

#endif // DETAILS_H
