cmake_minimum_required(VERSION 3.8.0)
project (MaterialDesigner)

# Main exe
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/Source/*.cpp)
set(CMAKE_CXX_STANDARD 11)

add_library(MaterialDesignerLib ${SRC_FILES})
add_executable(MaterialDesigner ${SRC_FILES})

# Tests
enable_testing()
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/Tests/*.cpp)
add_subdirectory(Lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(UnitTests ${TEST_SRC_FILES})

target_link_libraries(UnitTests gtest gtest_main)
target_link_libraries(UnitTests MaterialDesignerLib)

add_test(Tests UnitTests)