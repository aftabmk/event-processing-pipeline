add_library(exchange_type STATIC
    exchangetype.cpp
)

target_include_directories(exchange_type
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
