add_definitions(-DUNICODE)

file(GLOB_RECURSE SRC_FILES *.cpp)
list(REMOVE_ITEM SRC_FILES App/MaterialDesigner.cpp)

include_directories(./)

add_library(MaterialDesignerLib ${SRC_FILES})
target_link_libraries(MaterialDesignerLib imgui_node_editor)

add_executable(MaterialDesigner WIN32 App/MaterialDesigner.cpp ../Resources/Resource.rc)

target_link_libraries(MaterialDesigner MaterialDesignerLib)
target_link_libraries(MaterialDesigner d3d11 dxgi)
target_link_libraries(MaterialDesigner directxtk)

add_custom_command(TARGET MaterialDesigner POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/Assets/ $<TARGET_FILE_DIR:MaterialDesigner>/Assets/)
