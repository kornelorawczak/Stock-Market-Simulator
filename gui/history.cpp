#include "history.h"
#include "ui_history.h"

History::History(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::History)
{
    ui->setupUi(this);

    // Set the number of rows and columns
    ui->historyTable->setRowCount(5);
    ui->historyTable->setColumnCount(6);

    // Set headers
    QStringList headers;
    headers << "name" << "price" << "date" << "quantity" << "side" << "profit";
    ui->historyTable->setHorizontalHeaderLabels(headers);

    // Set all sections to stretch
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
}

History::~History()
{
    delete ui;
}
