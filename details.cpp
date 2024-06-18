#include "details.h"
#include "ui_details.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QDir>

details::details(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::details)
{
    ui->setupUi(this);

    QFont font = ui->textEdit->font();
    font.setPointSize(16);
    ui->textEdit->setFont(font);

    QFont font2 = ui->textEdit_2->font();
    font2.setPointSize(16);
    ui->textEdit_2->setFont(font2);
}

details::~details()
{
    delete ui;
}

void details::updateDetails(const QString &instrumentName) {
    QString filePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../data/records.csv"); // Provide the actual path to the CSV file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file:" << filePath;
        return;
    }

    QTextStream in(&file);
    bool found = false;
    QString upperInstrumentName = instrumentName.toUpper(); // Convert input to uppercase

    while (!in.atEnd() && !found) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 2 && fields[0].trimmed() == instrumentName.trimmed()) {
            ui->nameLabel->setText(fields[0]);
            ui->priceLabel->setText(QString::number(fields[1].toDouble(), 'f', 2));
            found = true;
        }
    }

    if (!found) {
        QMessageBox::critical(this, "Error", "Instrument not found");
        QCoreApplication::exit(1);
    }

    file.close();

    loadChartData(QDir(QCoreApplication::applicationDirPath()).filePath("../../data/records.csv"));
}

#include <QtCharts/QValueAxis>

void details::loadChartData(const QString &chartFilePath) {
    QFile file(chartFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the file: " + chartFilePath);
        return;
    }

    QTextStream in(&file);
    QLineSeries *series = new QLineSeries();
    QStringList values;

    double maxValue = 0;  // To track the maximum y-value
    double minValue = std::numeric_limits<double>::max(); // Start with the largest possible double

    // Read the single line containing all values
    if (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        values = line.split(',');

        // Convert each value to double, add to series, and update max and min values
        for (int i = 0; i < values.size(); ++i) {
            double y = values.at(i).toDouble();
            series->append(i, y);
            if (y > maxValue) {
                maxValue = y;  // Update the maximum value found
            }
            if (y < minValue) {
                minValue = y;  // Update the minimum value found
            }
        }
    }

    file.close();

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Price Chart");

    // Apply the dark theme
    chart->setTheme(QChart::ChartThemeDark);

    // Set series color to light blue
    series->setColor(QColor("#ADD8E6"));

    // Scale the y-axis from the minimum value found to 105% of the maximum value
    auto yAxis = new QValueAxis();
    yAxis->setRange(minValue, maxValue * 1.05);
    chart->setAxisY(yAxis, series);

    auto xAxis = new QValueAxis();
    xAxis->setRange(0, values.size() - 1);
    xAxis->setTickInterval(1); // Ensures tick marks at every integer
    xAxis->setLabelFormat("%d"); // Format labels as integers
    xAxis->setTitleText("Days");
    chart->setAxisX(xAxis, series);

    // Check if a chart view already exists
    if (ui->chartWidget->layout() && ui->chartWidget->layout()->count() > 0) {
        QLayoutItem *child;
        while ((child = ui->chartWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget(); // safely delete the widget
            delete child; // delete the layout item
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout(); // Create layout if it doesn't exist
        ui->chartWidget->setLayout(layout);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartWidget->layout()->addWidget(chartView);
}
