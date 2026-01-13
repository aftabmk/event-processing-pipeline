#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "../nlohmann/json.hpp"

#include "../macro/logger.hpp"
#include "../utils/gzip_json.hpp"
#include "../instrument/Instrument.hpp"
#include "../filterclass/FilterClass.hpp"

using json = nlohmann::json;

/**
 * Executes full business logic for a single record.
 * Throws on failure.
 */
json process(const json& record);
