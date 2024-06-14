#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
#include <QTextStream>
#include <QFile>
#include <QFont>
#include <QMessageBox>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QWidget>

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
    void loadDataFromFile(const QString &filePath);
private:
    Ui::details *ui;
    void createChart(const QVector<double> &values);
};

#endif // DETAILS_H
