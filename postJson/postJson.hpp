#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Sends JSON payload via HTTP POST
void postJson(const json& payload);
