#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

namespace Ui {
class Chart;
}

class Chart : public QDialog
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr);
    ~Chart();
    void loadChartData(const QString &filename);

private:
    Ui::Chart *ui;
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;

};

#endif // CHART_H
