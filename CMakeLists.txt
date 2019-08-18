cmake_minimum_required(VERSION 3.8.0)
project (MaterialDesigner)

set(CMAKE_CXX_STANDARD 14)
option(ENABLE_TESTING "Turns on testing" OFF)

# DirectXTK
add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/DirectXTK)
include_directories(${PROJECT_SOURCE_DIR}/Lib/DirectXTK/Inc)

# Material Designer
add_subdirectory(Source)

# Tests
if (ENABLE_TESTING)
    enable_testing()

    include_directories(Source)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/googletest)
    add_subdirectory(Tests)
endif ()