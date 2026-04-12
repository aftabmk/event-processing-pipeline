#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

#include "nlohmann/json.hpp"

#include "macro/logger.hpp"
#include "processworkflow.hpp"

inline int run_local() {
    try {
        std::ifstream in("../data.json");
        // std::ifstream in("data.json");

        if (!in)
        {
            throw std::runtime_error("Failed to open data.json");
        }

        std::cout << "File opened successfully\n";

        json roots;
        try {
            in >> roots;   // isolate this
        }
        catch (const std::exception& e) {
            std::cerr << "JSON parse/read failed: " << e.what() << std::endl;
            throw;
        }
        // only get first object instead of whole array
        for(auto& root : roots){
            processWorkFlow(root);
        }
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());
        return 1;
    }

    return 0;
}