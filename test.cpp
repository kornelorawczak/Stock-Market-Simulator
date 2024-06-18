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




//map<string, double> Serializer::portfolio;

int main() {
    auto btc = CryptoApi("BTC");
    btc.refreshData();
    auto usd = Currency("USD");
    usd.refreshData();
    /* cout << btc.getValue() << endl;
    cout << btc.getMA() << endl;
    cout << btc.getVolatility() << endl;
    cout << btc.getMACD() << endl;
    auto gold = Gold();
    cout << gold.getMA() << endl;
    cout << gold.getVolatility() << endl;
    cout << gold.getMACD() << endl;
    */
     /*cout << btc.difference() << endl;
    double* chart_data = btc.monthly();
    for (int i = 0; i < 30; i++){
        cout << "Day " << (-1) * i << ": " << chart_data[i] << endl;
    }
     */
     //cout << usd.getValue() << endl;
    Serializer::performAction(usd, -100);
    //Serializer::performAction(btc, -10);
    return 0;
}
