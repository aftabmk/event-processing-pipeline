#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * Safety wrapper around process().
 * Prevents one bad record from killing the batch.
 */
void workflow(const json& record);
