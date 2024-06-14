#include "history.h"
#include "ui_history.h"
#include <QFileDialog>
#include <QMessageBox>

History::History(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::History)
{
    ui->setupUi(this);

    // Set the number of rows and columns
    ui->historyTable->setColumnCount(6);

    // Set headers
    QStringList headers;
    headers << "name" << "price" << "date" << "quantity" << "side" << "profit";
    ui->historyTable->setHorizontalHeaderLabels(headers);

    //adapt headers that they fit table size
    ui->historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->historyTable->setStyleSheet(
        "QHeaderView::section {"
        "background-color: black;"
        "color: white;"
        "border: none;"
        "}"
        "QTableCornerButton::section {"
        "background-color: black;"
        "border: none;"
        "}"
        "QTableWidget::item {"
        "border: none;"
        "}"
        );

    ui->historyTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->historyTable->verticalHeader()->setDefaultSectionSize(30);
    ui->historyTable->verticalHeader()->hide();

    loadCSVData();
}

History::~History()
{
    delete ui;
    saveCSVData();
}

void History::saveCSVData()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/history.csv";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file for writing: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    int rowCount = ui->historyTable->rowCount();
    int columnCount = ui->historyTable->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        QStringList rowData;
        for (int column = 0; column < columnCount; ++column) {
            QTableWidgetItem* item = ui->historyTable->item(row, column);
            if (item)
                rowData << item->text();
            else
                rowData << "";  // Handle null items
        }
        out << rowData.join(',') << "\n";
    }

    file.close();
}


void History::loadCSVData()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/history.csv";
    qDebug() << "File Path: " <<filePath;
    QFile file(filePath);

    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Failed to create file: " + file.errorString());
            return;
        }
        file.close(); // Close the newly created empty file
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QStringList lines = in.readAll().split('\n');
    file.close();

    ui->historyTable->setRowCount(lines.size());

    QFont font = ui->historyTable->font();
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

            ui->historyTable->setItem(row, column, newItem);
        }
    }
}
