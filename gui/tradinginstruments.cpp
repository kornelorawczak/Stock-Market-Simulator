#include "tradinginstruments.h"
#include "ui_tradinginstruments.h"
#include <QFileDialog>
#include <QMessageBox>

TradingInstruments::TradingInstruments(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TradingInstruments)
{
    ui->setupUi(this);

    ui->instrumentsTable->setColumnCount(4);

    // Set headers
    QStringList headers;
    headers << "name" << "quotes" << "change" << "category";
    ui->instrumentsTable->setHorizontalHeaderLabels(headers);

    // Set all sections to stretch
    ui->instrumentsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->instrumentsTable->setStyleSheet(
        "QHeaderView::section {"
        "background-color: black;"
        "color: white;"
        "border: none;"
        "font-size: 16pt;"
        "}"
        "QTableCornerButton::section {"
        "background-color: black;"
        "border: none;"
        "}"
        "QTableWidget::item {"
        "border: none;"
        "}"
        );

    ui->instrumentsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->instrumentsTable->verticalHeader()->setDefaultSectionSize(30);
    ui->instrumentsTable->verticalHeader()->hide();

    loadCSVData("C:/Users/G4M3R/Desktop/UWR/obiektowe/projekt/Stock-Market-Simulator/gui/data/instruments.csv");
}

TradingInstruments::~TradingInstruments()
{
    delete ui;
}

void TradingInstruments::loadCSVData(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QStringList lines = in.readAll().split('\n');
    file.close();

    ui->instrumentsTable->setRowCount(lines.size());

    QFont font = ui->instrumentsTable->font();
    font.setPointSize(12);

    for (int row = 0; row < lines.size(); ++row) {
        QString line = lines.at(row);
        if (line.isEmpty()) continue;

        QStringList items = line.split(',');

        for (int column = 0; column < items.size(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem(items.at(column));
            newItem->setFont(font); // Set font
            newItem->setTextAlignment(Qt::AlignCenter);

            //disable editing by user
            Qt::ItemFlags flags = newItem->flags();
            flags &= ~Qt::ItemIsEditable;
            newItem->setFlags(flags);

            ui->instrumentsTable->setItem(row, column, newItem);
        }
    }
}
