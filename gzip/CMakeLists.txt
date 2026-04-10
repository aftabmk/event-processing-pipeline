add_library(gzip
    GZipJson.cpp
)

target_include_directories(gzip
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(gzip
    PUBLIC
        ZLIB::ZLIB
)