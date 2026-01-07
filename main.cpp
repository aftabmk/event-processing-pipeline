#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "utils/gzip_json.hpp"
#include "instrument/instrument.hpp"
#include "filterclass/filterclass.hpp"

using json = nlohmann::json;

int main() {
    try {
        std::ifstream in("../data.json");
        if (!in)
            throw std::runtime_error("Failed to open ../data.json");

        json root;
        in >> root;

        if (!root.is_array())
            throw std::runtime_error("Expected array of records");

        for (const auto& record : root) {
            try {
                if (!record.contains("body"))
                    continue;

                const json& snsBody = record["body"];

                if (!snsBody.contains("Message"))
                    continue;

                const json& messageObj = snsBody["Message"];

                if (!messageObj.contains("type") || messageObj["type"] != "Buffer" || !messageObj.contains("data") || !messageObj["data"].is_array())
                    continue;

                // Extract gzip buffer
                std::vector<unsigned char> zipArray;
                zipArray.reserve(messageObj["data"].size());

                for (const auto& b : messageObj["data"]) {
                    zipArray.push_back(b.get<unsigned char>());
                }

                // Decompress
                json decompressedJSON = readGzippedJson(zipArray);

                // Process
                FilterClass filter(decompressedJSON.dump());
                std::unique_ptr<Instrument> instrument = filter.getInstrument();

                if (instrument) {
                    instrument->log();
                    json out = instrument->process(decompressedJSON);
                    std::cout << out.dump() << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Error processing record: " << e.what() << "\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
