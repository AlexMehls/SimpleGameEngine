cmake_minimum_required(VERSION 3.18)
project(GameEngineTest)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_subdirectory(Editor)

target_link_libraries(${PROJECT_NAME} PRIVATE Editor)