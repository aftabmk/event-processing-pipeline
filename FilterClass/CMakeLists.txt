add_library(filterclass STATIC
    filterclass.cpp
)

target_include_directories(filterclass
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
