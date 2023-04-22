cmake_minimum_required(VERSION 3.18)
project(GameEngineTest)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# target_include_directories(${PROJECT_NAME} PRIVATE ${LIBS_PATH}/include include)

add_subdirectory(GameEngine)

target_link_libraries(${PROJECT_NAME} PRIVATE GameEngine)