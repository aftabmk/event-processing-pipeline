#pragma once
#include <string>
#include "../Enums/Enums.hpp"

class ExchangeType {
public:
    static Type toType(const std::string& s);
    static Exchange toExchange(const std::string& s);
};
