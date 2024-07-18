#ifndef DATA
#define DATA

#include <iostream>
#include <string>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDateTime>
#include <cmath>

using namespace std;

class Data : public QObject {
    Q_OBJECT
private:
    virtual void parseData(const QString& jsonData, double& rate, int type) = 0;
    virtual double getPastValue(int days) = 0;
    virtual QString generateDate(int days) = 0;
public:
    virtual QString getName() const = 0;
    virtual void refreshData() = 0;
    virtual double getValue() const = 0;
    virtual double difference() = 0;
    virtual QVector<double> monthly() = 0;
    virtual double getMA() = 0;
    virtual double getVolatility() = 0;
    virtual double getMACD() = 0;
};

class MovingAverage {
public:
    static double calculate(const QVector<double>& prices, int days);
};

class Volatility {
public:
    static double calculate(const QVector<double>& prices, int days);
};

class MACD {
public:
    static double calculate(const QVector<double>& prices, int daysShort, int daysLong);
};

class CryptoApi : public Data {
    Q_OBJECT
private:
    const QString apiKey = "YOUR_CRYPTOCOMPARE_API_KEY";
    QString id;
    double currentValue = 0.0;
    QString baseUrl;
    QVector<double> prices;
    bool done = false;
    void parseData(const QString& jsonData, double& rate, int type) override;
    QString generateDate(int days) override;
    double getPastValue(int days) override;
public:
    CryptoApi(const QString& name);
    void refreshData() override;
    double getValue() const override;
    double difference() override;
    QVector<double> monthly() override;
    QString getName() const override;
    double getMA() override;
    double getVolatility() override;
    double getMACD() override;
};


class NBPApi : public Data {
    Q_OBJECT
protected:
    QString host;
    QString path;
    double current_price;
    QVector<double> prices;
    bool done = false;
    QString generateDate(int days) override;
    void parseData(const QString& jsonData, double& rate, int type) override = 0;
    double getPastValue(int days) override = 0;
public:
    void refreshData() override;
    double getValue() const override;
    double difference() override;
    QVector<double> monthly() override;
    QString getName() const override = 0;
    double getMA() override;
    double getVolatility() override;
    double getMACD() override;
};


class Currency : public NBPApi {
    Q_OBJECT
private:
    QString id;
    void parseData(const QString& jsonData, double& rate, int type) override;
    double getPastValue(int days) override;
public:
    Currency(const QString& id);
    QString getName() const override;
};

class Gold : public NBPApi {
    Q_OBJECT
private:
    void parseData(const QString& jsonData, double& rate, int type) override;
    double getPastValue(int days) override;
public:
    Gold();
    QString getName() const override;
};

#endif // DATA
