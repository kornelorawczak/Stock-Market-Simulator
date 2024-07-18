#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDateTime>
#include <cmath>
#include "data.h"

double MovingAverage::calculate(const QVector<double>& prices, int days) {
    double sum = 0.0;
    for (int i = 0; i < days; i++) {
        sum += prices[i];
    }
    return sum / days;
}

double Volatility::calculate(const QVector<double>& prices, int days) {
    double sum = 0.0, mean, variance = 0.0;
    for (int i = 0; i < days; ++i) {
        sum += prices[i];
    }
    mean = sum / days;
    for (int i = 0; i < days; ++i) {
        variance += pow(prices[i] - mean, 2);
    }
    variance /= days;
    return sqrt(variance);
}

double MACD::calculate(const QVector<double>& prices, int daysShort, int daysLong) {
    double shortMA = MovingAverage::calculate(prices, daysShort);
    double longMA = MovingAverage::calculate(prices, daysLong);
    return shortMA - longMA;
}

void CryptoApi::parseData(const QString& jsonData, double& rate, int type) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    if (type == 1) rate = jsonObj["USD"].toDouble();
    else rate = jsonObj["BTC"].toObject()["USD"].toDouble();
}

QString CryptoApi::generateDate(int days) {
    QDateTime now = QDateTime::currentDateTimeUtc();
    QDateTime target = now.addDays(-days);
    qint64 epochTime = target.toSecsSinceEpoch();
    return QString::number(epochTime);
}


double CryptoApi::getPastValue(int days) {
    QString date = generateDate(days);
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(baseUrl + "/data/pricehistorical?fsym=" + id + "&tsyms=USD&ts=" + date + "&api_key=" + apiKey));
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    double pastDayRate = 0.0;
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        parseData(response, pastDayRate, 2);
    } else {
        cerr << "Failed to refresh data: " << reply->errorString().toStdString() << endl;
    }
    reply->deleteLater();
    return pastDayRate;
}

CryptoApi::CryptoApi(const QString& name) : id(name), baseUrl("https://min-api.cryptocompare.com") {}

void CryptoApi::refreshData() {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(baseUrl + "/data/price?fsym=" + id + "&tsyms=USD&api_key=" + apiKey));
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        parseData(response, currentValue, 1);
    } else {
        throw runtime_error("Failed to refresh data from API");
    }
    reply->deleteLater();
}

double CryptoApi::getValue() const {
    return currentValue;
}

double CryptoApi::difference() {
    double pastValue = getPastValue(1);
    return ((currentValue - pastValue) / pastValue) * 100;
}

QVector<double> CryptoApi::monthly() {
    prices.clear();
    for (int i = 0; i < 30; ++i) {
        prices.append(getPastValue(i));
    }
    done = true;
    return prices;
}

QString CryptoApi::getName() const {
    return id;
}

double CryptoApi::getMA() {
    if (!done) monthly();
    return MovingAverage::calculate(prices, 30);
}

double CryptoApi::getVolatility() {
    if (!done) monthly();
    return Volatility::calculate(prices, 30);
}

double CryptoApi::getMACD() {
    if (!done) monthly();
    return MACD::calculate(prices, 12, 26);
}

QString NBPApi::generateDate(int days) {
    QDate date = QDate::currentDate().addDays(-days);
    return date.toString("yyyy-MM-dd");
}

void NBPApi::refreshData() {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(host + path));
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        parseData(response, current_price, 1);
    } else {
        cerr << "Failed to get data from NBP API. HTTP status: " << reply->errorString().toStdString() << endl;
    }
    reply->deleteLater();
}

double NBPApi::getValue() const {
    return current_price;
}

double NBPApi::difference() {
    double yesterdayValue = getPastValue(1);
    return ((current_price - yesterdayValue) / yesterdayValue) * 100;
}

QVector<double> NBPApi::monthly() {
    prices.clear();
    prices.append(getValue());
    int i = 1;
    int j = 1;
    while (i < 30) {
        try {
            prices.append(getPastValue(j));
            i++;
            j++;
        } catch (const exception& e) {
            j++;
            continue;
        }
    }
    done = true;
    return prices;
}

double NBPApi::getMA() {
    if (!done) monthly();
    return MovingAverage::calculate(prices, 30);
}

double NBPApi::getVolatility() {
    if (!done) monthly();
    return Volatility::calculate(prices, 30);
}

double NBPApi::getMACD() {
    if (!done) monthly();
    return MACD::calculate(prices, 12, 26);
}

void Currency::parseData(const QString& jsonData, double& rate, int type) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    rate = jsonObj["rates"].toArray()[0].toObject()["mid"].toDouble();
}

double Currency::getPastValue(int days) {
    QString dateStr = generateDate(days);
    QString pastUrl = "/api/exchangerates/rates/A/" + id + "/" + dateStr + "/?format=json";
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(host + pastUrl));
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    double pastDayRate = 0.0;
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        parseData(response, pastDayRate, 1);
    } else {
        throw exception();
    }
    reply->deleteLater();
    return pastDayRate;
}

Currency::Currency(const QString& id) {
    this->id = id;
    this->host = "http://api.nbp.pl";
    this->path = "/api/exchangerates/rates/A/" + id + "/?format=json";
}

QString Currency::getName() const {
    return id;
}

void Gold::parseData(const QString& jsonData, double& rate, int type) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject jsonObj = jsonDoc.array()[0].toObject();
    rate = jsonObj["cena"].toDouble();
}

double Gold::getPastValue(int days) {
    QString dateStr = generateDate(days);
    QString pastUrl = "/api/cenyzlota/" + dateStr + "/?format=json";
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(host + pastUrl));
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    double pastDayRate = 0.0;
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        parseData(response, pastDayRate, 1);
    } else {
        throw exception();
    }
    reply->deleteLater();
    return pastDayRate;
}

Gold::Gold() {
    this->host = "http://api.nbp.pl";
    this->path = "/api/cenyzlota/?format=json";
}

QString Gold::getName() const {
    return "GOLD";
}
