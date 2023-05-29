set(SOURCES src/behavior.cpp src/behaviorLookup.cpp src/behaviorIncludes_impl.cpp)

set(BEHAVIORS_PATH ../../../testBehaviors)
file(GLOB BEHAVIORS_SOURCES CONFIGURE_DEPENDS ${BEHAVIORS_PATH}/src/*.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include generated ${BEHAVIORS_PATH}/include)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES} ${BEHAVIORS_SOURCES})