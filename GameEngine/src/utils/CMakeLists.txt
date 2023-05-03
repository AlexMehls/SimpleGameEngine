set(SOURCES src/idGenerator.cpp src/coordinateTransform.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})
