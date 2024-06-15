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

class Serializer {
private:
    static map<string, double> portfolio;
    static void loadPortfolio();
    static void savePortfolio();
    static void updatePortfolio(const string& assetName, double quantity);
public:
    static void performAction(const Data& asset, double quantity);
    static void deleteHistory();
    static void deletePortfolio();
};