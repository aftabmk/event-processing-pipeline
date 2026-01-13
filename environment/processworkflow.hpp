#pragma once

#include <memory>
#include <future>
#include <vector>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "macro/logger.hpp"
#include "workflow/workflow.hpp"

using json = nlohmann::json;

inline void processWorkFlow(const json& root)
{
    if (!root.is_array())
        throw std::runtime_error("Expected top-level array");

    auto workflow = std::make_shared<Workflow>();
    std::vector<std::future<void>> futures;

    // Outer array
    for (const auto& wrapper : root) {
        if (!wrapper.contains("Records") || !wrapper["Records"].is_array()) {
            LOG("Record not found!");
            continue;
        }

        // Records array
        for (const auto& record : wrapper["Records"]) {
            futures.emplace_back(
                std::async(std::launch::async, [workflow, record]() {
                    workflow->execute(record);
                })
            );
        }
    }

    // Wait for all tasks + catch async exceptions
    for (auto& future : futures) {
        try {
            future.get();
        }
        catch (const std::exception& e) {
            LOG_ERR(e.what());
        }
    }
}
