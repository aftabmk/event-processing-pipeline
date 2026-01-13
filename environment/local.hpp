#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

#include "nlohmann/json.hpp"

#include "macro/logger.hpp"
#include "processworkflow.hpp"

inline int local() {
    try {
        std::ifstream in;
        in.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            in.open("../data.json");
        } 
        catch (const std::ios_base::failure& e) {
            RUNTIME_ERROR(e.what());
        }

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
