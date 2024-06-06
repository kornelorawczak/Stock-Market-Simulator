#include <iostream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>


using namespace std;
using namespace nlohmann;
using namespace httplib;

class Data {
private:
    virtual void parseData(const string& jsonData, double& rate) = 0;
    virtual double getPastValue(int days) = 0;
    virtual string generateDate(int days) = 0;
public:
    virtual void refreshData() = 0;
    virtual double getValue() = 0;
    virtual double difference() = 0;
    virtual double* monthly() = 0;
};

class NBPApi : public Data {
protected:
    string host;
    string path;
    double current_price;
    double monthly_rates[30];
    string generateDate(int days) override {
        auto now = chrono::system_clock::now();
        auto past = now - chrono::hours(24 * days);

        time_t tt = chrono::system_clock::to_time_t(past);
        tm local_tm = *localtime(&tt);

        ostringstream oss;
        oss << put_time(&local_tm, "%Y-%m-%d");
        string dateStr = oss.str();

        return dateStr;
    }

    void parseData(const string& jsonData, double& rate) override = 0;
    double getPastValue(int days) override = 0;
public:
    void refreshData() override {
        Client cli(host.c_str());
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            parseData(res->body, current_price);
        } else {
            cerr << "Failed to get data from NBP API. HTTP status: " << (res ? res->status : -1) << endl;
        }
    }
    double getValue() override {
        return current_price;
    }

    double difference() override {
        double yesterdayValue = getPastValue(1);
        return ((current_price - yesterdayValue)/yesterdayValue) * 100;
    }

    double* monthly() override {
        monthly_rates[0] = getValue();
        int i = 1;
        int j = 1;
        while(i < 30){
            try {
                monthly_rates[i] = getPastValue(j);
                i++;
                j++;
            }
            catch(const exception &e){
                j++;
                continue;
            }
        }
        return monthly_rates;
    }
};


class Currency : public NBPApi {
private:
    string id;
    void parseData(const string& jsonData, double& rate) override {
        try {
            auto json = json::parse(jsonData);
            rate = json["rates"][0]["mid"].get<double>();
        } catch (const exception& e) {
            cerr << "Failed to parse JSON data: " << e.what() << endl;
        }
    }
    double getPastValue(int days) override {
        string dateStr = generateDate(days);
        string pastUrl = "/api/exchangerates/rates/A/" + id + "/" + dateStr + "/?format=json";
        Client cli(host.c_str());
        auto res = cli.Get(pastUrl);
        double pastDayRate = 0.0;
        if (res && res->status == 200) {
            parseData(res->body, pastDayRate);
        } else {
            throw exception();
            //cerr << "Failed to get data from NBP API for the previous day. HTTP status: " << (res ? res->status : -1) << endl;
        }

        return pastDayRate;
    }
public:
    Currency(const string& id){
        this->id = id;
        this->host = "api.nbp.pl";
        this->path = "/api/exchangerates/rates/A/" + id + "/?format=json";
    }
};

class Gold : public NBPApi {
private:
    void parseData(const string& jsonData, double& rate) override {
        try {
            auto json = json::parse(jsonData);
            rate = json[0]["cena"].get<double>();
        } catch (const exception& e) {
            cerr << "Failed to parse JSON data: " << e.what() << endl;
        }
    }
    double getPastValue(int days) override {
        string dateStr = generateDate(days);
        string pastUrl = "/api/cenyzlota/" + dateStr + "/?format=json";
        Client cli(host.c_str());
        auto res = cli.Get(pastUrl);
        double pastDayRate = 0.0;
        if (res && res->status == 200) {
            parseData(res->body, pastDayRate);
        } else {
            throw exception();
            //cerr << "Failed to get data from NBP API for the previous day. HTTP status: " << (res ? res->status : -1) << endl;
        }

        return pastDayRate;
    }
public:
    Gold() {
        this->host = "api.nbp.pl";
        this->path = "/api/cenyzlota/?format=json";
    }
};


int main() {
    /*cout << "USD: " << endl;
    auto usd = Currency("USD");
    usd.refreshData();
    cout << usd.getValue() << endl;
    cout << usd.difference() << endl;
    double* chart_data = usd.monthly();
    for (int i = 0; i < 30; i++){
        cout << "Day " + to_string((-1) * i) + ": " + to_string(chart_data[i]) << endl;
    }
    cout << endl << "GDP:" << endl;
    auto gbp = Currency("GBP");
    gbp.refreshData();
    cout << gbp.getValue() << endl;
    cout << gbp.difference() << endl;
    double* chart_data2 = gbp.monthly();
    for (int i = 0; i < 30; i++){
        cout << "Day " + to_string((-1) * i) + ": " + to_string(chart_data2[i]) << endl;
    }*/

    auto gold = Gold();
    gold.refreshData();
    cout << gold.getValue() << endl;
    cout << gold.difference() << endl;
    double* chart_data3 = gold.monthly();
    for (int i = 0; i < 30; i++){
        cout << "Day " + to_string((-1) * i) + ": " + to_string(chart_data3[i]) << endl;
    }
    return 0;
}

// todo:
// zwinąć złoto w klasę currency i zmienić jej nazwę na NBPApi_Data