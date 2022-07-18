# ---> demo 11 (render to texture)
add_executable(d11_render_to_texture
  geometry_triangle.cpp 
  main.cpp)
target_include_directories(d11_render_to_texture PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d11_render_to_texture PUBLIC util-core-3.3)
set_target_properties(d11_render_to_texture PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d11_render_to_texture 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vshader_rtt=shader_d11_rtt_vertex.glsl
  fshader_rtt=shader_d11_rtt_fragment.glsl
  vshader_quad=shader_passthrough.glsl
  fshader_quad=shader_wobbly_texture.glsl)
