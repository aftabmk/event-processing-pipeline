#pragma once
#include <vector>
#include <nlohmann/json_fwd.hpp>

nlohmann::json readGzippedJson(const std::vector<unsigned char>& data);
