#include <vector>
#include <future>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "../nlohmann/json.hpp"
#include "future/future.hpp"
#include "option/option.hpp"

using json = nlohmann::json;

// ---------------------- Job definition ----------------------
struct Job {
    std::string file;        // input file
    std::string output;      // output file
    json (*processor)(const json&);
};

// ---------------------- JSON loader -------------------------
json load_json(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open input file: " + path);

    json data;
    file >> data;
    return data;
}

// ---------------------- Job runner --------------------------
void run_job(const Job& job) {
    // Load input
    json input = load_json(job.file);

    // Process
    json output = job.processor(input);

    // Ensure output directory exists
    std::filesystem::path outPath(job.output);
    std::filesystem::create_directories(outPath.parent_path());

    // Write output
    std::ofstream ofs(outPath);
    if (!ofs.is_open())
        throw std::runtime_error("Failed to open output file: " + outPath.string());

    ofs << output.dump(4);
}

// ---------------------- Main --------------------------------
int main() {
    try {
        std::vector<Job> jobs = {
            {"data/nse_future.json",  "result/nse_future.json",  &Future::processFutureNSE},
            {"data/bse_future.json",  "result/bse_future.json",  &Future::processFutureBSE},
            {"data/nse_option.json",  "result/nse_option.json",  &Option::processOptionNSE},
            {"data/bse_option.json",  "result/bse_option.json",  &Option::processOptionBSE},
        };

        std::vector<std::future<void>> futures;

        // Launch jobs asynchronously
        for (const auto& job : jobs) {
            futures.emplace_back(
                std::async(std::launch::async, run_job, std::cref(job))
            );
        }

        // Wait for all jobs and propagate exceptions
        for (auto& f : futures) {
            f.get();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
