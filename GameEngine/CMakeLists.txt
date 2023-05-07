cmake_minimum_required(VERSION 3.18)
project(GameEngine)

set(LIBS_PATH Libs)

find_library(glfwlib glfw NAME GLFW glfw3 PATHS ${LIBS_PATH}/lib)
message(STATUS "GLFW found as ${glfwlib}")

find_library(assimplib assimp NAME Assimp assimp-vc143-mt PATHS ${LIBS_PATH}/lib)
message(STATUS "assimp found as ${assimplib}")

add_library(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBS_PATH}/include)

add_subdirectory(external/glad)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC ${glfwlib} glad ${assimplib})