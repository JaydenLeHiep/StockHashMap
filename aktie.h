//
// Created by Hiep Le on 04.03.23.
//

#ifndef ABGABE1_AKTIE_H
#define ABGABE1_AKTIE_H
#include <iostream>
#include <string>

//Date,Open,High,Low,Close,Adj Close,Volume
using namespace std;
struct StockData {
    string date;
    float open;
    float high;
    float low;
    float close;
    float adj_close;
    int volume;
    StockData* next;
};

struct Aktie {
    std::string name;
    std::string WKN;
    std::string kurz;
    StockData StockData;
};



#endif //ABGABE1_AKTIE_H
