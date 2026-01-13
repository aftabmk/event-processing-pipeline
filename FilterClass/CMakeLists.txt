add_library(filterclass STATIC
    FilterClass.cpp
)

target_include_directories(filterclass
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
