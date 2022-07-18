# ---> demo 14 (simple geometry shader)
add_executable(d14_geometry_shader main.cpp)
target_include_directories(d14_geometry_shader PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d14_geometry_shader PUBLIC util-core-3.3)
set_target_properties(d14_geometry_shader PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d14_geometry_shader 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vs=shader_d14.vs.glsl
  gs=shader_d14.gs.glsl
  fs=shader_d14.fs.glsl)
