#pragma once

#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

#include "processworkflow.hpp"
#include "macro/logger.hpp"

inline int local() {
    try {
        std::ifstream in("../data.json");
        if (!in)
            RUNTIME_ERROR("Failed to open ../data.json");

        json root;
        in >> root;

        processWorkFlow(root);
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());
        return 1;
    }

    return 0;
}
