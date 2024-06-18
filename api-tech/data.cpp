#include <iostream>
#include <string>
#include <httplib.h>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cmath>
#include "data.hpp"


using namespace std;
using namespace nlohmann;
using namespace httplib;

double MovingAverage::calculate(const double* prices, int days){
    double sum = 0.0;
    for (int i = 0; i < days; i++){
        sum += prices[i];
    }
    return sum / days;
}

double Volatility::calculate(const double* prices, int days) {
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



double MACD::calculate(const double* prices, int daysShort, int daysLong) {
    double shortMA = MovingAverage::calculate(prices, daysShort);
    double longMA = MovingAverage::calculate(prices, daysLong);
    return shortMA - longMA;
}



void CryptoApi::parseData(const string& jsonData, double& rate, int type) {
    auto json = json::parse(jsonData);
    //cout << json << endl;
    if (type == 1) rate = json["USD"].get<double>();
    else rate = json["BTC"]["USD"].get<double>();
}
string CryptoApi::generateDate(int days) {
    time_t now = time(nullptr);
    time_t target = now - (days * 86400);
    ostringstream oss;
    oss << put_time(gmtime(&target), "%s");
    return oss.str();
}
double CryptoApi::getPastValue(int days) {
    string date = generateDate(days);
    Client cli(baseUrl);
    string endpoint = "/data/pricehistorical?fsym=" + id + "&tsyms=USD&ts=" + date + "&api_key=" + apiKey;
    double pastDayRate = 0.0;
    auto res = cli.Get(endpoint);
    if (res && res->status == 200) {
        parseData(res->body, pastDayRate, 2);
    }
    else {
        cerr << "Failed to refresh data: " << (res ? res->status : -1) << endl;
    }
    return pastDayRate;
}

CryptoApi::CryptoApi(const string& name) : id(name), baseUrl("https://min-api.cryptocompare.com") {}

void CryptoApi::refreshData() {
    Client cli(baseUrl);
    string endpoint = "/data/price?fsym=" + id + "&tsyms=USD&api_key=" + apiKey;
    auto res = cli.Get(endpoint);

    if (res && res->status == 200) {
        parseData(res->body, currentValue, 1);
    } else {
        throw runtime_error("Failed to refresh data from API");
    }
}
double CryptoApi::getValue() const {
    return currentValue;
}

double CryptoApi::difference() {
    double pastValue = getPastValue(1);
    return ((currentValue - pastValue) / pastValue) * 100;
}

double* CryptoApi::monthly() {
    for (int i = 0; i < 30; ++i) {
        prices[i] = getPastValue(i);
    }
    done = true;
    return prices;
}
string CryptoApi::getName() const {
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


string NBPApi::generateDate(int days) {
    auto now = chrono::system_clock::now();
    auto past = now - chrono::hours(24 * days);

    time_t tt = chrono::system_clock::to_time_t(past);
    tm local_tm = *localtime(&tt);

    ostringstream oss;
    oss << put_time(&local_tm, "%Y-%m-%d");
    string dateStr = oss.str();

    return dateStr;
}
void NBPApi::refreshData() {
    Client cli(host.c_str());
    auto res = cli.Get(path.c_str());

    if (res && res->status == 200) {
        parseData(res->body, current_price, 1);
    } else {
        cerr << "Failed to get data from NBP API. HTTP status: " << (res ? res->status : -1) << endl;
    }
}
double NBPApi::getValue() const {
    return current_price;
}

double NBPApi::difference() {
    double yesterdayValue = getPastValue(1);
    return ((current_price - yesterdayValue)/yesterdayValue) * 100;
}

double* NBPApi::monthly() {
    prices[0] = getValue();
    int i = 1;
    int j = 1;
    while(i < 30){
        try {
            prices[i] = getPastValue(j);
            i++;
            j++;
        }
        catch(const exception &e){
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


void Currency::parseData(const string& jsonData, double& rate, int type) {
    try {
        auto json = json::parse(jsonData);
        rate = json["rates"][0]["mid"].get<double>();
    } catch (const exception& e) {
        cerr << "Failed to parse JSON data: " << e.what() << endl;
    }
}
double Currency::getPastValue(int days) {
    string dateStr = generateDate(days);
    string pastUrl = "/api/exchangerates/rates/A/" + id + "/" + dateStr + "/?format=json";
    Client cli(host.c_str());
    auto res = cli.Get(pastUrl);
    double pastDayRate = 0.0;
    if (res && res->status == 200) {
        parseData(res->body, pastDayRate, 1);
    } else {
        throw exception();
        //cerr << "Failed to get data from NBP API for the previous day. HTTP status: " << (res ? res->status : -1) << endl;
    }

    return pastDayRate;
}
Currency::Currency(const string& id){
    this->id = id;
    this->host = "api.nbp.pl";
    this->path = "/api/exchangerates/rates/A/" + id + "/?format=json";
}
string Currency::getName() const {
    return id;
}

void Gold::parseData(const string& jsonData, double& rate, int type) {
    try {
        auto json = json::parse(jsonData);
        rate = json[0]["cena"].get<double>();
    } catch (const exception& e) {
        cerr << "Failed to parse JSON data: " << e.what() << endl;
    }
}
double Gold::getPastValue(int days) {
    string dateStr = generateDate(days);
    string pastUrl = "/api/cenyzlota/" + dateStr + "/?format=json";
    Client cli(host.c_str());
    auto res = cli.Get(pastUrl);
    double pastDayRate = 0.0;
    if (res && res->status == 200) {
        parseData(res->body, pastDayRate, 1);
    } else {
        throw exception();
        //cerr << "Failed to get data from NBP API for the previous day. HTTP status: " << (res ? res->status : -1) << endl;
    }

    return pastDayRate;
}
Gold::Gold() {
    this->host = "api.nbp.pl";
    this->path = "/api/cenyzlota/?format=json";
}
string Gold::getName() const {
    return "GOLD";
}
