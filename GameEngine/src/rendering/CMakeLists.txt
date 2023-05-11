set(SOURCES src/renderObject.cpp src/shader.cpp src/primitiveObjects.cpp src/camera.cpp src/mesh.cpp src/texture.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
