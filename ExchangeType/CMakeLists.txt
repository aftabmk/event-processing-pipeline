add_library(exchangetype STATIC
    ExchangeType.cpp
)

target_include_directories(exchangetype
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
