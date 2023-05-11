cmake_minimum_required(VERSION 3.18)
project(GameEngine)

set(LIBS_PATH Libs)

find_library(glfwlib glfw NAME GLFW glfw3 PATHS ${LIBS_PATH}/lib)
message(STATUS "GLFW found as ${glfwlib}")

add_library(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBS_PATH}/include)

add_subdirectory(external/glad)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)
add_subdirectory(external/assimp)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC ${glfwlib} glad assimp)
