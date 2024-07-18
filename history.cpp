#include "history.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>

History::History(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    historyTable = new QTableWidget(this);
    setupTable();
    layout->addWidget(historyTable);
    setLayout(layout);

    setDarkTheme();
}

void History::setupTable()
{
    QStringList headers = {"Name", "Price", "Date", "Quantity"};
    historyTable->setColumnCount(headers.size());
    historyTable->setHorizontalHeaderLabels(headers);
    historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void History::setDarkTheme()
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
    historyTable->setStyleSheet(darkStyle);
}

void History::loadHistory(const QString &filePath)
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

void History::populateTable(const QStringList &data)
{
    historyTable->setRowCount(data.size());

    for (int i = 0; i < data.size(); ++i) {
        QStringList row = data[i].split(',');

        for (int j = 0; j < row.size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(row[j]);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make the item non-editable
            historyTable->setItem(i, j, item);
        }
    }
}
