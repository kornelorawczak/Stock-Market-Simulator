#include <iostream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>


using namespace std;
using namespace nlohmann;
using namespace httplib;

class Usd {
private:
    string host;
    string path;
    double usd_rate;
    void parseData(const std::string& jsonData, double& rate) {
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

        string pastURL = "/api/exchangerates/rates/A/USD/" + dateStr + "/?format=json";
        return pastURL;
    }
    double getYesterdayValue(){
        string yesterdayUrl = generateDateUrl(1);
        Client cli(host.c_str());
        auto res = cli.Get(yesterdayUrl);
        double previousDayRate = 0.0;
        if (res && res->status == 200) {
            parseData(res->body, previousDayRate);
        } else {
            std::cerr << "Failed to get data from NBP API for the previous day. HTTP status: " << (res ? res->status : -1) << std::endl;
        }

        return previousDayRate;
    }
public:
    Usd() : host("api.nbp.pl"), path("/api/exchangerates/rates/A/USD/?format=json") {}

    void refreshData() {
        Client cli(host.c_str());
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            parseData(res->body, usd_rate);
        } else {
            cerr << "Failed to get data from NBP API. HTTP status: " << (res ? res->status : -1) << endl;
        }
    }

    double getValue(){
        return usd_rate;
    }

    double difference(){
        return getYesterdayValue();
    }
};


int main() {
    auto test = Usd();
    test.refreshData();
    cout << test.getValue() << endl;
    cout << test.difference() << endl;
    return 0;
}

// todo:
// - zmień funkcje .difference() tab aby zwracała procent zmiany w ostatnich 24h
// - funkcja .monthly() która zwraca tabele wartości ostatnich 30 dni do zrobienia wykresu
// - owinąć to w klase bardziej abstrakcyjną assets, tak aby klasa usd to jedynie wywołanie konstruktora assets z odpowiednim linkiem