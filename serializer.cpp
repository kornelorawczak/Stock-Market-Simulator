#include <iostream>
#include <string>
#include <httplib.h>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cmath>
#include "serializer.hpp"
#include "data.hpp"

using namespace std;
using namespace nlohmann;
using namespace httplib;

map<string, double> Serializer::portfolio;
double Serializer::freeFunds;
double Serializer::allocatedFunds;

void Serializer::loadBalance() {
    ifstream file("balance.csv");
    if (!file.is_open()) {
        cerr << "Can't open balance file" << endl;
        return;
    }
    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        iss >> freeFunds >> allocatedFunds;
    }
    file.close();
}


void Serializer::saveBalance() {
    ofstream file("balance.csv");
    if (!file.is_open()){
        cerr << "Can't open balance file to write in" << endl;
        return;
    }
    file << freeFunds << " " << allocatedFunds << endl;
    file.close();
}


void Serializer::changeAllocatedFunds(double amount) {
    loadBalance();
    allocatedFunds += amount;
    saveBalance();
}

void Serializer::changeFreeFunds(double amount) {
    loadBalance();
    if (freeFunds + amount < 0){
        throw invalid_argument("Not enough free funds to make this purchase");
    }
    freeFunds += amount;
    saveBalance();
}

void Serializer::loadPortfolio(){
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
void Serializer::savePortfolio() {
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
void Serializer::updatePortfolio(const string& assetName, double quantity){
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
void Serializer::performAction(const Data& asset, double quantity){
    if (quantity < 0 && portfolio[asset.getName()] > quantity){
        throw invalid_argument("Can't sell what you don't have!");
    }
    changeFreeFunds(asset.getValue() * (-1) * quantity);
    changeAllocatedFunds(asset.getValue() * quantity);
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
void Serializer::deleteHistory(){
    ofstream file("history.csv", ios_base::trunc);
    file.close();
}
void Serializer::deletePortfolio(){
    ofstream file("portfolio.csv", ios_base::trunc);
    file.close();
}

