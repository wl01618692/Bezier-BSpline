# ---> demo 2 (usage of imgui + opengl2)
add_executable(d2_imgui_opengl2 main_opengl2.cpp)
target_link_libraries(d2_imgui_opengl2 PUBLIC util-compatible)
set_target_properties(d2_imgui_opengl2 PROPERTIES CXX_STANDARD 11)

# ---> demo 3 (usage of imgui + opengl3)
add_executable(d2_imgui_opengl3 main_opengl3.cpp)
target_link_libraries(d2_imgui_opengl3 PUBLIC util-core-3.3)
set_target_properties(d2_imgui_opengl3 PROPERTIES CXX_STANDARD 11)
