#include "process.hpp"

#include <memory>
#include <vector>
#include <iostream>

#include "utils/gzip_json.hpp"
#include "instrument/instrument.hpp"
#include "filterclass/filterclass.hpp"

void process(const json& record)
{
    if (!record.contains("body"))
        return;

    const json& snsBody = record["body"];

    if (!snsBody.contains("Message"))
        return;

    const json& messageObj = snsBody["Message"];

    if (!messageObj.contains("type") ||
        messageObj["type"] != "Buffer" ||
        !messageObj.contains("data") ||
        !messageObj["data"].is_array())
        return;

    // Extract gzip buffer
    std::vector<unsigned char> zipArray;
    zipArray.reserve(messageObj["data"].size());

    for (const auto& b : messageObj["data"]) {
        zipArray.push_back(b.get<unsigned char>());
    }

    // Decompress gzip → JSON
    json decompressedJSON = readGzippedJson(zipArray);

    // Filter → Instrument
    FilterClass filter(decompressedJSON.dump());
    std::unique_ptr<Instrument> instrument = filter.getInstrument();

    if (!instrument)
        return;

    instrument->log();

    json out = instrument->process(decompressedJSON);
    std::cout << out.dump() << "\n";
}
