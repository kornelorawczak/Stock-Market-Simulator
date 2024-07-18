#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "serializer.h"
#include "data.h"
#include <QCoreApplication>

using namespace std;

QMap<QString, double> Serializer::portfolio;
double Serializer::freeFunds = 0.0;
double Serializer::allocatedFunds = 0.0;

void Serializer::loadBalance() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/balance.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cerr << "Can't open balance file" << endl;
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    if (!line.isNull()) {
        QStringList fields = line.split(" ");
        if (fields.size() == 2) {
            freeFunds = fields[0].toDouble();
            allocatedFunds = fields[1].toDouble();
        }
    }
    file.close();
}

void Serializer::saveBalance() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/balance.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cerr << "Can't open balance file to write in" << endl;
        return;
    }
    QTextStream out(&file);
    out << freeFunds << " " << allocatedFunds << "\n";
    file.close();
}

void Serializer::changeAllocatedFunds(double amount) {
    loadBalance();
    allocatedFunds += amount;
    saveBalance();
}

void Serializer::changeFreeFunds(double amount) {
    loadBalance();
    if (freeFunds + amount < 0) {
        throw invalid_argument("Not enough free funds to make this purchase");
    }
    freeFunds += amount;
    saveBalance();
}

void Serializer::loadPortfolio() {
    QFile portfolioFile(QCoreApplication::applicationDirPath() + "/../../data/portfolio.csv");
    if (!portfolioFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cerr << "Can't open portfolio.csv!" << endl;
        return;
    }
    QTextStream in(&portfolioFile);
    portfolio.clear();
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() == 2) {
            QString id = fields[0];
            double qty = fields[1].toDouble();
            portfolio[id] = qty;
        }
    }
    portfolioFile.close();
}

void Serializer::savePortfolio() {
    QFile portfolioFile(QCoreApplication::applicationDirPath() + "/../../data/portfolio.csv");
    if (!portfolioFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cerr << "Nie można otworzyć pliku portfolio.csv!" << endl;
        return;
    }
    QTextStream out(&portfolioFile);
    QMapIterator<QString, double> i(portfolio);
    while (i.hasNext()) {
        i.next();
        out << i.key() << " " << i.value() <<  "\n";
    }
    portfolioFile.close();
}

void Serializer::updatePortfolio(const QString& assetName, double quantity) {
    loadPortfolio();
    if (portfolio.contains(assetName)) {
        if (quantity > 0) {
            portfolio[assetName] += quantity;
        } else {
            if (portfolio[assetName] + quantity < 0) {
                throw runtime_error("Can't sell that much!");
            }
            portfolio[assetName] += quantity;
        }
    } else {
        if (quantity < 0) {
            throw runtime_error("Can't sell that much!");
        }
        portfolio[assetName] = quantity;
    }
    savePortfolio();
}

void Serializer::performAction(const Data& asset, double quantity) {
    loadPortfolio();
    if (quantity < 0 && portfolio[asset.getName()] < (-1) * quantity) {
        qDebug () << quantity << " " << portfolio[asset.getName()];
        throw invalid_argument("Can't sell what you don't have!");
    }
    changeFreeFunds(asset.getValue() * (-1) * quantity);
    changeAllocatedFunds(asset.getValue() * quantity);

    QFile historyFile(QCoreApplication::applicationDirPath() + "/../../data/history.csv");
    if (!historyFile.open(QIODevice::Append | QIODevice::Text)) {
        cerr << "File can't be open!" << endl;
        return;
    }
    QTextStream out(&historyFile);
    QDateTime now = QDateTime::currentDateTime();
    QString dateStr = now.toString("yyyy-MM-dd");
    out << asset.getName() << "," << asset.getValue() << "," << dateStr << "," << quantity <<  "\n";
    historyFile.close();
    updatePortfolio(asset.getName(), quantity);
}

void Serializer::deleteHistory() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/history.csv");
    if (file.exists()) {
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.close();
    }
}

void Serializer::deletePortfolio() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/portfolio.csv");
    if (file.exists()) {
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.close();
    }
}
