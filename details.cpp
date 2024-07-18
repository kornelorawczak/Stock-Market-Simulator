#include "details.h"
#include "ui_details.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "serializer.h"

details::details(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::details)
    , instrumentObject(nullptr)
{
    ui->setupUi(this);

    QFont font = ui->nameLabel->font();
    font.setPointSize(16);
    ui->nameLabel->setFont(font);

    QFont font2 = ui->priceLabel->font();
    font2.setPointSize(16);
    ui->priceLabel->setFont(font2);

    connect(ui->buyButton, &QPushButton::clicked, this, &details::onBuyButtonClicked);
    connect(ui->sellButton, &QPushButton::clicked, this, &details::onSellButtonClicked);
}

details::~details()
{
    delete ui;
    if (instrumentObject) {
        delete instrumentObject;
    }
}

void details::updateDetails(const QString &instrumentName) {
    QString filePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../data/records.csv");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file:" << filePath;
        return;
    }

    QTextStream in(&file);
    bool found = false;
    QString upperInstrumentName = instrumentName.toUpper();

    while (!in.atEnd() && !found) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() > 1 && fields[0].trimmed() == instrumentName.trimmed()) {
            ui->nameLabel->setText(fields[0]);
            ui->priceLabel->setText(QString::number(fields[1].toDouble(), 'f', 2));
            found = true;

            if (fields[0] == "GOLD") {
                instrumentObject = new Gold();
            } else if (fields[0] == "USD") {
                instrumentObject = new Currency("USD");
            } else if (fields[0] == "EUR") {
                instrumentObject = new Currency("EUR");
            } else if (fields[0] == "BTC") {
                instrumentObject = new CryptoApi("BTC");
            } else if (fields[0] == "JPY") {
                instrumentObject = new CryptoApi("JPY");
            } else if (fields[0] == "GBP") {
                instrumentObject = new Currency("GBP");
            }

            if (instrumentObject) {
                instrumentObject->refreshData();
            }
        }
    }

    if (!found) {
        QMessageBox::critical(this, "Error", "Instrument not found");
        QCoreApplication::exit(1);
    }

    file.close();
    loadChartData(filePath);
    loadIndicators(filePath);
}

void details::loadChartData(const QString &chartFilePath) {
    QFile file(chartFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the file: " + chartFilePath);
        return;
    }

    QTextStream in(&file);
    QLineSeries *series = new QLineSeries();
    QStringList values;

    double maxValue = 0;
    double minValue = std::numeric_limits<double>::max();

    if (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        values = line.split(',');

        for (int i = 1; i < values.size(); ++i) {
            double y = values.at(i).toDouble();
            series->append(i - 1, y);
            if (y > maxValue) {
                maxValue = y;
            }
            if (y < minValue) {
                minValue = y;
            }
        }
    }

    file.close();
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Price Chart");

    chart->setTheme(QChart::ChartThemeDark);

    series->setColor(QColor("#ADD8E6"));

    auto yAxis = new QValueAxis();
    yAxis->setRange(minValue, maxValue * 1.05);
    chart->setAxisY(yAxis, series);

    auto xAxis = new QValueAxis();
    xAxis->setRange(0, values.size() - 2);
    xAxis->setTickInterval(1);
    xAxis->setLabelFormat("%d");
    xAxis->setTitleText("Days");
    chart->setAxisX(xAxis, series);

    if (ui->chartWidget->layout() && ui->chartWidget->layout()->count() > 0) {
        QLayoutItem *child;
        while ((child = ui->chartWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout();
        ui->chartWidget->setLayout(layout);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartWidget->layout()->addWidget(chartView);
}

void details::loadIndicators(const QString &chartFilePath) {
    QFile file(chartFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the file: " + chartFilePath);
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines.append(in.readLine().trimmed());
    }

    file.close();

    if (lines.size() < 3) {
        QMessageBox::critical(this, "Error", "Not enough data to read indicators.");
        return;
    }

    QString maValue = lines.at(lines.size() - 3);
    QString volatilityValue = lines.at(lines.size() - 2);
    QString macdValue = lines.at(lines.size() - 1);

    ui->MAlabel->setText("MA = " + maValue);
    ui->Volatilitylabel->setText("Volatility = " + volatilityValue);
    ui->MACDlabel->setText("MACD = " + macdValue);
}

void details::onBuyButtonClicked() {
    bool ok;
    double quantity = ui->textEdit->toPlainText().toDouble(&ok);

    if (!ok || quantity <= 0) {
        QMessageBox::critical(this, "Error", "Please enter a valid quantity to buy.");
        return;
    }

    try {
        Serializer::performAction(*instrumentObject, quantity);
        QMessageBox::information(this, "Success", "Successfully bought " + QString::number(quantity) + " units of " + instrumentObject->getName());
        emit balanceUpdated();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void details::onSellButtonClicked() {
    bool ok;
    double quantity = ui->textEdit_2->toPlainText().toDouble(&ok);

    if (!ok || quantity <= 0) {
        QMessageBox::critical(this, "Error", "Please enter a valid quantity to sell.");
        return;
    }

    try {
        Serializer::performAction(*instrumentObject, -quantity);
        QMessageBox::information(this, "Success", "Successfully sold " + QString::number(quantity) + " units of " + instrumentObject->getName());
        emit balanceUpdated();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
