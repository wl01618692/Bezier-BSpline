# ---> demo 4 (matrices)
add_executable(d4_matrices main.cpp)
target_include_directories(d4_matrices PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d4_matrices PUBLIC util-core-3.3)
set_target_properties(d4_matrices PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d4_matrices 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=shader_d4_transform.glsl
  fragmentshader=shader_d4_color.glsl)
