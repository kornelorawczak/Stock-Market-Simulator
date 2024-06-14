#include "details.h"
#include "ui_details.h"

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
    QString filePath = "C:/Users/G4M3R/Desktop/UWR/obiektowe/projekt/instruments.csv"; // Provide the actual path to the CSV file
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

    loadDataFromFile("C:/Users/G4M3R/Desktop/UWR/obiektowe/projekt/records.csv");
    file.close();
}

void details::loadDataFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file:" << filePath;
        return;
    }

    QVector<double> values;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        values.append(line.toDouble());
    }

    file.close();

    createChart(values);
}

void details::createChart(const QVector<double> &values) {

}
