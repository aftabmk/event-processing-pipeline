#include "GzipJson.hpp"

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

// ---------------- Base64 Decode ----------------
std::vector<unsigned char> GzipJson::base64Decode(const std::string& input) {
    std::vector<unsigned char> output;
    std::vector<int> T(256, -1);

    for (int i = 0; i < 64; i++) {
        T[base64_chars[i]] = i;
    }

    int val = 0, valb = -8;

    for (unsigned char c : input) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            output.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return output;
}

// ---------------- GZIP → JSON ----------------
GzipJson::json GzipJson::parse(const std::string& base64Data) {
    // Step 1: Base64 decode
    std::vector<unsigned char> compressed = base64Decode(base64Data);

    if (compressed.empty()) {
        throw std::runtime_error("Base64 decode failed");
    }

    // Step 2: Validate GZIP header
    if (compressed.size() >= 2) {
        if (!(compressed[0] == 0x1F && compressed[1] == 0x8B)) {
            throw std::runtime_error("Not valid GZIP data");
        }
    }

    // Step 3: Setup zlib
    z_stream zs{};
    zs.next_in = reinterpret_cast<Bytef*>(compressed.data());
    zs.avail_in = static_cast<uInt>(compressed.size());

    if (inflateInit2(&zs, 16 + MAX_WBITS) != Z_OK) {
        throw std::runtime_error("inflateInit2 failed");
    }

    std::vector<unsigned char> decompressed;
    unsigned char buffer[32768];

    int ret;
    do {
        zs.next_out = buffer;
        zs.avail_out = sizeof(buffer);

        ret = inflate(&zs, Z_NO_FLUSH);

        if (ret != Z_OK && ret != Z_STREAM_END) {
            inflateEnd(&zs);
            throw std::runtime_error("inflate failed");
        }

        size_t bytesProduced = sizeof(buffer) - zs.avail_out;
        decompressed.insert(decompressed.end(), buffer, buffer + bytesProduced);

    } while (ret != Z_STREAM_END);

    inflateEnd(&zs);

    // Step 4: Convert + parse
    std::string jsonStr(decompressed.begin(), decompressed.end());
    return json::parse(jsonStr);
}