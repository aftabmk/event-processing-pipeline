#pragma once
#include <string>
#include <memory>
#include "../Enums/Enums.hpp"

class Instrument;

class FilterClass {
private:
    Type typeEnum = Type::UNKNOWN;
    Exchange exchangeEnum = Exchange::UNKNOWN;

    // 🔥 entire try-catch lives here
    static std::pair<Exchange, Type> parseJson(const std::string& jsonStr);

public:
    explicit FilterClass(const std::string& jsonStr);

    bool match(Exchange exchange, Type type) const;
    std::unique_ptr<Instrument> getInstrument() const;
};
