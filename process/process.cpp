#include "process.hpp"

#include <memory>
#include <vector>
#include <iostream>

#include "utils/gzip_json.hpp"
#include "instrument/instrument.hpp"
#include "filterclass/filterclass.hpp"

json process(const json& record) {
    if (!record.contains("body"))
        return json::object();

    const json& snsBody = record["body"];
    if (!snsBody.contains("Message"))
        return json::object();

    const json& messageObj = snsBody["Message"];
    if (!messageObj.contains("type") || messageObj["type"] != "Buffer" ||
        !messageObj.contains("data") || !messageObj["data"].is_array())
        return json::object();

    std::vector<unsigned char> zipArray;
    zipArray.reserve(messageObj["data"].size());

    for (const auto& b : messageObj["data"])
        zipArray.push_back(b.get<unsigned char>());

    json decompressedJSON = readGzippedJson(zipArray);

    FilterClass filter(decompressedJSON.dump());
    std::unique_ptr<Instrument> instrument = filter.getInstrument();

    if (!instrument)
        return json::object();

    instrument->log();
    return instrument->process(decompressedJSON);
}
