#pragma once
#include <cstdlib>

namespace ENV {
    inline const char* URL = std::getenv("URL");
    inline const char* KEY = std::getenv("KEY");
    inline const char* isLambda = std::getenv("ENV"); 
    inline const char* EXCHANGE_1 = std::getenv("EXCHANGE_1");
    inline const char* EXCHANGE_2 = std::getenv("EXCHANGE_2");
}