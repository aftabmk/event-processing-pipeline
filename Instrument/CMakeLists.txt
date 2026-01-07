add_library(instrument STATIC
    equity/equity.cpp
    future/future.cpp
    option/option.cpp
)

target_include_directories(instrument
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
