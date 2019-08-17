ADD_DEFINITIONS(-DUNICODE)

file(GLOB SRC_FILES *.cpp)

link_directories(${PROJECT_SOURCE_DIR}/Bin/CMake)

add_library(MaterialDesignerLib ${SRC_FILES})
add_executable(MaterialDesigner WIN32 ${SRC_FILES} ../Resources/Resource.rc)

target_link_libraries(MaterialDesigner d3d11 dxgi)
target_link_libraries(MaterialDesigner DirectXTK)