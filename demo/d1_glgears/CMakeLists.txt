# ---> demo 1 (famous glxgears)
add_executable(d1_glgears main.cpp draw.cpp)
target_link_libraries(d1_glgears PUBLIC util-compatible)
set_target_properties(d1_glgears PROPERTIES CXX_STANDARD 11)
