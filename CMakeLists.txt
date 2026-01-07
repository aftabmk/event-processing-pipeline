cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

# --------------------
# C++ standard
# --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------
# Executable
# --------------------
add_executable(main
    main.cpp
    filterclass/filterclass.cpp
    exchangetype/exchangetype.cpp
    instrument/equity/equity.cpp
    instrument/future/future.cpp
    instrument/option/option.cpp
    utils/gzip_json.cpp
)

# --------------------
# Include paths
# --------------------
target_include_directories(main
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

# --------------------
# Dependencies
# --------------------
find_package(ZLIB REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# --------------------
# Link libraries
# --------------------
target_link_libraries(main
    PRIVATE
        ZLIB::ZLIB
        nlohmann_json::nlohmann_json
)

# --------------------
# Compile definitions
# --------------------
target_compile_definitions(main PRIVATE HAVE_ZLIB)
