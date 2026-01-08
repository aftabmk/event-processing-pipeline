#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * Executes full business logic for a single record.
 * Throws on failure.
 */
json process(const json& record);
