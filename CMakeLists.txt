cmake_minimum_required(VERSION 3.8.0)
project (MaterialDesigner)

set(CMAKE_CXX_STANDARD 14)
option(ENABLE_TESTING "Turns on testing" OFF)

# Add module files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# DirectXTK
add_subdirectory(Lib/DirectXTK)
include_directories(Lib/DirectXTK/Inc)

# ImGui
include_directories(Lib/imgui/imgui)

# ImGui Node Editor
find_package(imgui_node_editor REQUIRED)
set(IMGUI_NODE_EDITOR_DIR Lib/imgui-node-editor)
include_directories(${IMGUI_NODE_EDITOR_DIR}/NodeEditor/Include)

# Material Designer
add_subdirectory(Source)

# Tests
if (ENABLE_TESTING)
    enable_testing()

    include_directories(Source)
    add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/googletest)
    add_subdirectory(Tests)
endif ()