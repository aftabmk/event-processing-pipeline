#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include "workflow/workflow.hpp"

using json = nlohmann::json;

int main() {
    try {
        std::ifstream in("../data.json");
        if (!in)
            throw std::runtime_error("Failed to open ../data.json");

        json root;
        in >> root;

        if (!root.is_array())
            throw std::runtime_error("Expected top-level array");

        auto workflow = std::make_unique<Workflow>();

        // root -> array of objects
        for (const auto& wrapper : root) {
            if (!wrapper.contains("Records") || !wrapper["Records"].is_array())
                continue; // skip malformed entries

            // Records -> array (batching enabled)
            for (const auto& record : wrapper["Records"]) {
                try {
                    workflow->execute(record);
                }
                catch (const std::exception& e) {
                    // Do NOT kill the entire batch for one bad message
                    std::cerr << "Error processing record: " << e.what() << "\n";
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
