# ---> demo 5 (drawing a colored cube)
add_executable(d5_colored_cube main.cpp)
target_include_directories(d5_colored_cube PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d5_colored_cube PUBLIC util-core-3.3)
set_target_properties(d5_colored_cube PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d5_colored_cube 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=shader_d5_vertex.glsl
  fragmentshader=shader_d5_fragment.glsl)
