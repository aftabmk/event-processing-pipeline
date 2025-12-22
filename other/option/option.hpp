#pragma once

#include <string>
#include <utility>
#include <cmath>
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

class Option {
public:
    // ---------- Side processors ----------
    static json processNSE(const json& side);
    static json processBSE(const json& side, bool isCE);

    // ---------- Option chain ----------
    static json processOptionNSE(const json& jsonData);
    static json processOptionBSE(const json& jsonData);

    // ---------- Helpers ----------
    static int    toInt(const json& j, const char* key);
    static double toDouble(const json& j, const char* key);
    static std::pair<int, int> calculateBound(double underlyingValue, int multiplier, int count);

    // ---------- Option builder ----------
    static json buildOption(
        int strike,
        double underlyingValue,
        const std::string& timestamp,
        const std::string& underlying,
        const std::string& expiry,
        const json& ce,
        const json& pe
    );
};
