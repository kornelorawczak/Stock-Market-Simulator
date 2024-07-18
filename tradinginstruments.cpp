#include "tradinginstruments.h"
#include "ui_tradinginstruments.h"
#include "details.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include "data.h"

TradingInstruments::TradingInstruments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TradingInstruments)
{
    ui->setupUi(this);

    setupTable();

    setDarkTheme();

    connect(ui->instrumentsTable, &QTableWidget::cellClicked, this, &TradingInstruments::onCellClicked);
}

TradingInstruments::~TradingInstruments()
{
    delete ui;
}

void TradingInstruments::setupTable()
{
    QStringList headers = {"Name", "Price", "24h Chg"};
    ui->instrumentsTable->setColumnCount(headers.size());
    ui->instrumentsTable->setHorizontalHeaderLabels(headers);
    ui->instrumentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TradingInstruments::setDarkTheme()
{
    QString darkStyle = R"(
        QTableWidget {
            background-color: #2b2b2b;
            color: #ffffff;
            gridline-color: #444444;
        }
        QHeaderView::section {
            background-color: #444444;
            color: #ffffff;
        }
        QTableWidget QTableCornerButton::section {
            background-color: #444444;
        }
        QScrollBar:vertical {
            background-color: #2b2b2b;
            width: 15px;
            margin: 20px 0 20px 0;
        }
        QScrollBar::handle:vertical {
            background-color: #444444;
            min-height: 20px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background-color: #2b2b2b;
            height: 20px;
            subcontrol-origin: margin;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )";
    ui->instrumentsTable->setStyleSheet(darkStyle);
}

void TradingInstruments::loadInstruments(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open file: " + filePath);
        return;
    }

    QTextStream in(&file);
    QStringList data;

    while (!in.atEnd()) {
        QString line = in.readLine();
        data.append(line);
    }

    file.close();
    populateTable(data);
}

void TradingInstruments::populateTable(const QStringList &data)
{
    ui->instrumentsTable->setRowCount(data.size());

    for (int i = 0; i < data.size(); ++i) {
        QStringList row = data[i].split(',');

        for (int j = 0; j < row.size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(row[j]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            ui->instrumentsTable->setItem(i, j, item);
        }
    }
}

void TradingInstruments::onCellClicked(int row, int column) {
    if (column == 0) {
        QString instrumentName = ui->instrumentsTable->item(row, column)->text();
        Data* instrumentObject = nullptr;

        if (instrumentName == "GOLD") {
            instrumentObject = new Gold();
        } else if (instrumentName == "USD") {
            instrumentObject = new Currency("USD");
        } else if (instrumentName == "EUR") {
            instrumentObject = new Currency("EUR");
        } else if (instrumentName == "BTC") {
            instrumentObject = new CryptoApi("BTC");
        } else if (instrumentName == "JPY") {
            instrumentObject = new Currency("JPY");
        } else if (instrumentName == "GBP") {
            instrumentObject = new Currency("GBP");
        }

        if (instrumentObject) {
            instrumentObject->refreshData();
            QVector<double> prices = instrumentObject->monthly();

            QFile file(QCoreApplication::applicationDirPath() + "/../../data/records.csv");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::critical(this, "Error", "Could not open record file for writing.");
                delete instrumentObject;
                return;
            }

            QTextStream out(&file);
            out << instrumentName;
            for (double price : prices) {
                out << "," << price;
            }
            out << "\n";
            out << instrumentObject->getMA() << "\n";
            out << instrumentObject->getVolatility() << "\n";
            out << instrumentObject->getMACD() << "\n";
            file.close();

            details *detailsWindow = new details(this);
            detailsWindow->updateDetails(instrumentName);
            detailsWindow->setAttribute(Qt::WA_DeleteOnClose);
            detailsWindow->show();

            delete instrumentObject;
        }
    }
}
