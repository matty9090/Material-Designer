file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/Tests/*.cpp)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(UnitTests ${TEST_SRC_FILES})

target_link_libraries(UnitTests gtest gtest_main)
target_link_libraries(UnitTests MaterialDesignerLib)

add_test(Tests UnitTests)