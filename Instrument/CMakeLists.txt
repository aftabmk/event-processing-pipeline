add_library(instrument STATIC
    Equity/Equity.cpp
    Future/Future.cpp
    Option/Option.cpp
)

target_include_directories(instrument
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
