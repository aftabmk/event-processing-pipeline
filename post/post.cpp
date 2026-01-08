#include "post.hpp"

#include <curl/curl.h>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Load env safely (lazy, once)
static std::string getUrl() {
    const char* v = std::getenv("URL");
    if (!v || !*v)
        throw std::runtime_error("URL env var not set");
    return std::string(v);
}


static std::string getAnonKey() {
    const char* v = std::getenv("KEY");
    if (!v || !*v)
        throw std::runtime_error("KEY env var not set");
    return std::string(v);
}


void postJson(const json& payload) {
    CURL* curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("Failed to init curl");

    std::string body = payload.dump();

    struct curl_slist* headers = nullptr;
    std::string authHeader =
        "Authorization: Bearer " + getAnonKey();

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, authHeader.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, getUrl().c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        throw std::runtime_error(curl_easy_strerror(res));
}
