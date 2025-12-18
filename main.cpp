#include <iostream>
#include "Instrument/Instrument.hpp"
#include "FilterClass/FilterClass.hpp"

int main() {
    std::string jsonStr1 = R"({"exchange": "BSE", "type": "FUTURE", "data" : []})",
                jsonStr2 = R"({"exchange": "BSE", "type": "EQUITY", "data" : []})";

    FilterClass f1(jsonStr1), f2(jsonStr2);

    auto instrument_1 = f1.getInstrument(), 
         instrument_2 = f2.getInstrument();

    if (instrument_1) instrument_1->log();
    if (instrument_2) instrument_2->log();
}
