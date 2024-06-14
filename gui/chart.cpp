#include "chart.h"
#include "ui_chart.h"
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>

Chart::Chart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Chart)
    , chartView(new QChartView(this))
    , chart(new QChart())
    , series(new QLineSeries())
{
    ui->setupUi(this);

    // Load the chart data from the CSV file
    //loadChartData("C:/Users/G4M3R/Desktop/UWR/obiektowe/projekt/records.csv");

    // Set up the chart
    chart->addSeries(series);
    chart->createDefaultAxes();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the dialog layout
    QVBoxLayout *layout = new QVBoxLayout(ui->chartWid);
    layout->addWidget(chartView);
}

Chart::~Chart()
{
    delete ui;
}

void Chart::loadChartData(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    int x = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(',');

        for (const QString &value : values) {
            bool ok;
            double y = value.toDouble(&ok);
            if (ok) {
                series->append(x, y);
                ++x;
            }
        }
    }

    file.close();
}
