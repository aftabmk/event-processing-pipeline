#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <zlib.h>
#include <nlohmann/json.hpp>
#include <cppcodec/base64_rfc4648.hpp>

#include "FilterClass/FilterClass.hpp"

/* ---------------- gzip decompress ---------------- */
std::string gzipDecompress(const std::vector<uint8_t>& input) {
    z_stream zs{};
    zs.next_in = const_cast<Bytef*>(input.data());
    zs.avail_in = input.size();

    if (inflateInit2(&zs, 16 + MAX_WBITS) != Z_OK)
        throw std::runtime_error("inflateInit2 failed");

    std::string output;
    char buffer[32768];

    int ret;
    do {
        zs.next_out = reinterpret_cast<Bytef*>(buffer);
        zs.avail_out = sizeof(buffer);

        ret = inflate(&zs, 0);

        if (output.size() < zs.total_out)
            output.append(buffer, zs.total_out - output.size());

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END)
        throw std::runtime_error("gzip decompression failed");

    return output;
}

/* ---------------- main ---------------- */
int main() {
    try {
        /* 1️⃣ Read data.json */
        std::ifstream in("../data.json");
        if (!in)
            throw std::runtime_error("Failed to open data.json");

        nlohmann::json arr;
        in >> arr;

        for (const auto& msg : arr) {
            try {
                /* 2️⃣ Extract BASE64 STRING */
                std::string b64 = msg.get<std::string>();

                /* 3️⃣ Base64 decode */
                std::vector<uint8_t> compressed = cppcodec::base64_rfc4648::decode<std::vector<uint8_t>>(b64);
                

                /* 4️⃣ GZIP decompress */
                std::string decompressed = gzipDecompress(compressed);

                /* 🔍 DEBUG (do not skip this once) */
                std::cout << decompressed << "\n";

                /* 5️⃣ Parse JSON */
                nlohmann::json j = nlohmann::json::parse(decompressed);

                /* 6️⃣ Your pipeline */
                FilterClass f(decompressed);
                auto instrument = f.getInstrument();
                if (instrument)
                    instrument->log();
            }
            catch (const std::exception& e) {
                std::cerr << "Message error: " << e.what() << '\n';
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << '\n';
    }
}
