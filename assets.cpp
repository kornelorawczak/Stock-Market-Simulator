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
    virtual string generateDateUrl(int days) = 0;
public:
    virtual void refreshData() = 0;
    virtual double getValue() = 0;
    virtual double difference() = 0;
    virtual double* monthly() = 0;
};


class Currency : Data{
private:
    string host;
    string path;
    string id;
    double current_rate;
    double month_rates[30];
    void parseData(const string& jsonData, double& rate) override {
        try {
            auto json = json::parse(jsonData);
            rate = json["rates"][0]["mid"].get<double>();
        } catch (const exception& e) {
            cerr << "Failed to parse JSON data: " << e.what() << endl;
        }
    }
    string generateDateUrl(int days) {
        auto now = chrono::system_clock::now();
        auto past = now - chrono::hours(24*days);

        time_t tt = chrono::system_clock::to_time_t(past);
        tm local_tm = *localtime(&tt);

        ostringstream oss;
        oss << put_time(&local_tm, "%Y-%m-%d");
        string dateStr = oss.str();

        string pastURL = "/api/exchangerates/rates/A/" + id + "/" + dateStr + "/?format=json";
        return pastURL;
    }
    double getPastValue(int days) override {
        string yesterdayUrl = generateDateUrl(days);
        Client cli(host.c_str());
        auto res = cli.Get(yesterdayUrl);
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

    void refreshData() override {
        Client cli(host.c_str());
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            parseData(res->body, current_rate);
        } else {
            cerr << "Failed to get data from NBP API. HTTP status: " << (res ? res->status : -1) << endl;
        }
    }

    double getValue() override {
        return current_rate;
    }

    double difference() override {
        return ((current_rate - getPastValue(1))/getPastValue(1)) * 100;
    }

    double* monthly() override {
        month_rates[0] = getValue();
        int i = 1;
        int j = 1;
        while(i < 30){
            try {
                month_rates[i] = getPastValue(j);
                i++;
                j++;
            }
            catch(const exception &e){
                j++;
                continue;
            }
        }
        return month_rates;
    }
};


int main() {
    cout << "USD: " << endl;
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
    }
    return 0;
}

