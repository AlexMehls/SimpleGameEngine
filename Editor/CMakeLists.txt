cmake_minimum_required(VERSION 3.18)
project(Editor)

set(LIBS_PATH Libs)

add_library(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_subdirectory(../GameEngine ../GameEngine)
add_subdirectory(external/imgui)
#add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC GameEngine)
