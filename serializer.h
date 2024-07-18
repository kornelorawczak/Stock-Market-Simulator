#include <iostream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QMap>
#include "data.h"

using namespace std;

class Serializer {
private:
    static double freeFunds;
    static double allocatedFunds;
    static QMap<QString, double> portfolio;
    static void loadPortfolio();
    static void savePortfolio();
    static void changeFreeFunds(double amount);
    static void changeAllocatedFunds(double amount);
    static void loadBalance();
    static void saveBalance();
    static void updatePortfolio(const QString& assetName, double quantity);
public:
    static void performAction(const Data& asset, double quantity);
    static void deleteHistory();
    static void deletePortfolio();
};
