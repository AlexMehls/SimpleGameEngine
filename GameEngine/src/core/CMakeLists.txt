set(SOURCES src/gameEngine.cpp src/glfwCallbacks.cpp src/gameObject.cpp src/component.cpp src/behavior.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})