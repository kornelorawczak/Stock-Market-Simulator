#include <iostream>
#include <string>
#include <httplib.h>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>


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
};

class CryptoApi : public Data {
private:
    const string apiKey = "2b957ad8fc306a5241947642278291a9bec7444e7bd75a7aa9fbd16981fa8597";
    string id;
    double currentValue = 0.0;
    string baseUrl;
    void parseData(const string& jsonData, double& rate, int type) override {
        auto json = json::parse(jsonData);
        //cout << json << endl;
        if (type == 1) rate = json["USD"].get<double>();
        else rate = json["BTC"]["USD"].get<double>();
    }
    string generateDate(int days) override {
        time_t now = time(nullptr);
        time_t target = now - (days * 86400);
        ostringstream oss;
        oss << put_time(gmtime(&target), "%s");
        return oss.str();
    }
    double getPastValue(int days) override {
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
public:
    CryptoApi(const string& name) : id(name), baseUrl("https://min-api.cryptocompare.com") {}

    void refreshData() override {
        Client cli(baseUrl);
        string endpoint = "/data/price?fsym=" + id + "&tsyms=USD&api_key=" + apiKey;
        auto res = cli.Get(endpoint);

        if (res && res->status == 200) {
            parseData(res->body, currentValue, 1);
        } else {
            throw runtime_error("Failed to refresh data from API");
        }
    }
    double getValue() const override {
        return currentValue;
    }

    double difference() override {
        double pastValue = getPastValue(1);
        return ((currentValue - pastValue) / pastValue) * 100;
    }

    double* monthly() override {
        static double prices[30];
        for (int i = 0; i < 30; ++i) {
            prices[i] = getPastValue(i);
        }
        return prices;
    }
    string getName() const override {
        return id;
    }
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

    void parseData(const string& jsonData, double& rate, int type) override = 0;
    double getPastValue(int days) override = 0;
public:
    void refreshData() override {
        Client cli(host.c_str());
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            parseData(res->body, current_price, 1);
        } else {
            cerr << "Failed to get data from NBP API. HTTP status: " << (res ? res->status : -1) << endl;
        }
    }
    double getValue() const override {
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
    string getName() const override = 0;
};


class Currency : public NBPApi {
private:
    string id;
    void parseData(const string& jsonData, double& rate, int type) override {
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
            parseData(res->body, pastDayRate, 1);
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
    string getName() const override {
        return id;
    }
};

class Gold : public NBPApi {
private:
    void parseData(const string& jsonData, double& rate, int type) override {
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
            parseData(res->body, pastDayRate, 1);
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
    string getName() const override {
        return "GOLD";
    }
};

class Serializer {
private:
    static map<string, double> portfolio;
    static void loadPortfolio(){
        ifstream portfolioFile("portfolio.csv");
        if (!portfolioFile.is_open()) {
            cerr << "Can't open portfolio.csv!" << endl;
            return;
        }
        portfolio.clear();
        string line;
        while(getline(portfolioFile, line)){
            istringstream iss(line);
            string id;
            int qty;
            if (!(iss >> id >> qty)){
                break;
            }
            portfolio[id] = qty;
        }
        portfolioFile.close();
    }
    static void savePortfolio() {
        ofstream portfolioFile("portfolio.csv");
        if (!portfolioFile.is_open()) {
            cerr << "Nie można otworzyć pliku portfolio.csv!" << endl;
            return;
        }

        for (const auto& p : portfolio) {
            portfolioFile << p.first << " " << p.second << endl;
        }
        portfolioFile.close();
    }
    static void updatePortfolio(const string& assetName, double quantity){
        loadPortfolio();
        auto it = portfolio.find(assetName);
        if (it != portfolio.end()){
            if (quantity > 0) {
                it->second += quantity;
            }
            else{
                if (it->second + quantity < 0) {
                    throw runtime_error("Can't sell that much!");
                }
                it->second += quantity;
            }
        }
        else{
            if (quantity < 0){
                throw runtime_error("Can't sell that much!");
            }
            portfolio[assetName] = quantity;
        }
        savePortfolio();
    }
public:
    static void performAction(const Data& asset, double quantity){
        ofstream history_file("history.csv", ios_base::app);
        if (!history_file.is_open()) {
            cerr << "File can't be open!" << endl;
            return;
        }
        time_t now = time(nullptr);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", localtime(&now));
        history_file << asset.getName() << "," << asset.getValue() << "," << dateStr << "," << quantity << endl;
        if(!history_file){
            cerr << "File input error!" << endl;
        }
        history_file.close();
        updatePortfolio(asset.getName(), quantity);
    }
    static void deleteHistory(){
        ofstream file("history.csv", ios_base::trunc);
        file.close();
    }
    static void deletePortfolio(){
        ofstream file("portfolio.csv", ios_base::trunc);
        file.close();
    }
};

map<string, double> Serializer::portfolio;

int main() {
    auto btc = CryptoApi("BTC");
    btc.refreshData();
    cout << btc.getValue() << endl;
    /*cout << btc.difference() << endl;
    double* chart_data = btc.monthly();
    for (int i = 0; i < 30; i++){
        cout << "Day " << (-1) * i << ": " << chart_data[i] << endl;
    }
     */
    Serializer::performAction(btc, 20);
    Serializer::performAction(btc, -10);
    return 0;
}
