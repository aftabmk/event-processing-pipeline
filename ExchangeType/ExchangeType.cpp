#include "ExchangeType.hpp"

Exchange ExchangeType::toExchange(const std::string& str) {
    if (str == std::getenv("EXCHANGE_1")) return Exchange::EXCHANGE_1;
    if (str == std::getenv("EXCHANGE_2")) return Exchange::EXCHANGE_2;
    return Exchange::UNKNOWN;
}

Type ExchangeType::toType(const std::string& str) {
    if (str == "OPTION") return Type::OPTION;
    if (str == "FUTURE") return Type::FUTURE;
    if (str == "EQUITY") return Type::EQUITY;
    return Type::UNKNOWN;
}
