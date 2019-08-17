file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/Tests/*.cpp)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(LogTests ${TEST_SRC_FILES})

target_link_libraries(LogTests gtest gtest_main)
target_link_libraries(LogTests MaterialDesignerLib)

add_test(LogTests LogTests)