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
    void parseData(const std::string& jsonData) {
        try {
            auto json = json::parse(jsonData);
            usd_rate = json["rates"][0]["mid"].get<double>();
        } catch (const exception& e) {
            cerr << "Failed to parse JSON data: " << e.what() << endl;
        }
    }
public:
    Usd() : host("api.nbp.pl"), path("/api/exchangerates/rates/A/USD/?format=json") {}

    void refreshData() {
        Client cli(host.c_str());
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            parseData(res->body);
        } else {
            cerr << "Failed to get data from NBP API. HTTP status: " << (res ? res->status : -1) << endl;
        }
    }

    double getValue(){
        return usd_rate;
    }
};


int main() {
    auto test = Usd();
    test.refreshData();
    cout << test.getValue() << endl;
    return 0;
}

// todo:
// - funkcja .difference() która zwraca procent zmiany w ostatnich 24h
// - funkcja .monthly() która zwraca tabele wartości ostatnich 30 dni do zrobienia wykresu
// - owinąć to w klase bardziej abstrakcyjną assets, tak aby klasa usd to jedynie wywołanie konstruktora assets z odpowiednim linkiem