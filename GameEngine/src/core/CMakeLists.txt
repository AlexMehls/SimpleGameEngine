set(SOURCES src/gameEngine.cpp src/glfwCallbacks.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})