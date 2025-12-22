#pragma once
#include "../Instrument.hpp"
#include <iostream>

class Equity : public Instrument {
public:
    explicit Equity(Exchange exchange) : Instrument(exchange) {}

    void log() const override {
        if (exchange == Exchange::EXCHANGE_1) std::cout << "EXCHANGE_1\n";
        else if (exchange == Exchange::EXCHANGE_2) std::cout << "EXCHANGE_2\n";
        else std::cout << "UNKNOWN\n";
    }
};
