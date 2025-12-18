#include "ExchangeType.hpp"
#include <algorithm>
#include <cctype>

Exchange ExchangeType::toExchange(const std::string& str) {
    if (str == "NSE") return Exchange::NSE;
    if (str == "BSE") return Exchange::BSE;
    return Exchange::UNKNOWN;
}

Type ExchangeType::toType(const std::string& str) {
    if (str == "OPTION") return Type::OPTION;
    if (str == "FUTURE") return Type::FUTURE;
    if (str == "EQUITY") return Type::EQUITY;    
    return Type::UNKNOWN;
}
