set(SOURCES src/transform.cpp src/collider.cpp src/collisionDetection.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})