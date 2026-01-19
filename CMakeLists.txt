cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------- Dependencies ----------------
find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)

include_directories(
    ${CURL_INCLUDE_DIRS}
    /usr/local/include
)

link_directories(/usr/local/lib)

# ---------------- Submodules ----------------
add_subdirectory(utils)
add_subdirectory(process)
add_subdirectory(postJson)
add_subdirectory(workflow)
add_subdirectory(FilterClass)
add_subdirectory(ExchangeType)
add_subdirectory(Instrument)

# ---------------- Executable ----------------
add_executable(main main.cpp)

target_link_libraries(main
    PRIVATE
        workflow
        process
        utils
        postJson
        filterclass
        exchangetype
        instrument

        # AWS Lambda Runtime
        aws-lambda-runtime

        # System libraries
        ${CURL_LIBRARIES}
        ZLIB::ZLIB
        pthread
)
