set(SOURCES imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp  imgui.cpp backends/imgui_impl_opengl3.cpp backends/imgui_impl_glfw.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC backends ./)
target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})