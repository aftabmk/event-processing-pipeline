#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <zlib.h>
#include <nlohmann/json.hpp>

class GzipJson {
public:
    using json = nlohmann::json;

    static json parse(const std::string& base64Data);

private:
    static std::vector<unsigned char> base64Decode(const std::string& input);
};