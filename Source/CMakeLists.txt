ADD_DEFINITIONS(-DUNICODE)

file(GLOB_RECURSE SRC_FILES *.cpp)
list(REMOVE_ITEM SRC_FILES App/MaterialDesigner.cpp)

include_directories(./)

add_library(MaterialDesignerLib ${SRC_FILES})
add_executable(MaterialDesigner WIN32 App/MaterialDesigner.cpp ../Resources/Resource.rc)

target_link_libraries(MaterialDesigner MaterialDesignerLib)
target_link_libraries(MaterialDesigner d3d11 dxgi)
target_link_libraries(MaterialDesigner directxtk)