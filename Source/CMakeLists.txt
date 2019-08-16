file(GLOB SRC_FILES *.cpp)

add_library(MaterialDesignerLib ${SRC_FILES})
add_executable(MaterialDesigner ${SRC_FILES})