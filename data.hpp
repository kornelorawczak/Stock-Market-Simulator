#ifndef DATA
#define DATA

#include <iostream>
#include <string>
#include <httplib.h>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cmath>


using namespace std;
using namespace nlohmann;
using namespace httplib;

class Data {
private:
    virtual void parseData(const string& jsonData, double& rate, int type) = 0;
    virtual double getPastValue(int days) = 0;
    virtual string generateDate(int days) = 0;
public:
    virtual string getName() const = 0;
    virtual void refreshData() = 0;
    virtual double getValue() const = 0;
    virtual double difference() = 0;
    virtual double* monthly() = 0;
    virtual double getMA() = 0;
    virtual double getVolatility() = 0;
    virtual double getMACD() = 0;
};

class MovingAverage {
public:
    static double calculate(const double* prices, int days);
};

class Volatility {
public:
    static double calculate(const double* prices, int days);
};

class MACD {
public:
    static double calculate(const double* prices, int daysShort, int daysLong);
};

class CryptoApi : public Data {
private:
    const string apiKey = "2b957ad8fc306a5241947642278291a9bec7444e7bd75a7aa9fbd16981fa8597";
    string id;
    double currentValue = 0.0;
    string baseUrl;
    double prices[30];
    bool done = false;
    void parseData(const string& jsonData, double& rate, int type) override;
    string generateDate(int days) override;
    double getPastValue(int days) override;
public:
    CryptoApi(const string& name);
    void refreshData() override;
    double getValue() const override;
    double difference() override;
    double* monthly() override;
    string getName() const override;
    double getMA() override;
    double getVolatility() override;
    double getMACD() override;
};


class NBPApi : public Data {
protected:
    string host;
    string path;
    double current_price;
    double prices[30];
    bool done = false;
    string generateDate(int days) override;
    void parseData(const string& jsonData, double& rate, int type) override = 0;
    double getPastValue(int days) override = 0;
public:
    void refreshData() override;
    double getValue() const override;
    double difference() override;
    double* monthly() override;
    string getName() const override = 0;
    double getMA() override;
    double getVolatility() override;
    double getMACD() override;
};


class Currency : public NBPApi {
private:
    string id;
    void parseData(const string& jsonData, double& rate, int type) override;
    double getPastValue(int days) override;
public:
    Currency(const string& id);
    string getName() const override;
};

class Gold : public NBPApi {
private:
    void parseData(const string& jsonData, double& rate, int type) override;
    double getPastValue(int days) override;
public:
    Gold();
    string getName() const override;
};

#endif
