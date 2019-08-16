cmake_minimum_required(VERSION 3.8.0)
project (MaterialDesigner)

set(CMAKE_CXX_STANDARD 11)
option(ENABLE_TESTING "Turns on testing" OFF)

# Output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

# Main exe
add_subdirectory(Source)

# Tests
if (ENABLE_TESTING)
    enable_testing()

    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/googletest)
    add_subdirectory(Tests)
endif ()