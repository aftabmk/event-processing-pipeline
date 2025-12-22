#pragma once
#include "../Instrument.hpp"
#include <iostream>

class Option : public Instrument {
public:
    explicit Option(Exchange ex) : Instrument(ex) {}

    void log() const override {
        if (exchange == Exchange::EXCHANGE_1) std::cout << "EXCHANGE_1\n";
        else if (exchange == Exchange::EXCHANGE_2) std::cout << "EXCHANGE_2\n";
        else std::cout << "UNKNOWN\n";
    }
};
