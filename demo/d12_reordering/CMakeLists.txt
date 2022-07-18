# ---> demo 12 (how to order triangles)
add_executable(d12_reordering main.cpp)
target_include_directories(d12_reordering PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d12_reordering PUBLIC util-core-3.3)
set_target_properties(d12_reordering PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d12_reordering 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=shader_d12_transform.glsl
  fragmentshader=shader_d12_color.glsl)
