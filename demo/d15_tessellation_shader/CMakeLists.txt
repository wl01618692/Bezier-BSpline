add_executable(d15_tessellation_shader main.cpp)
target_include_directories(d15_tessellation_shader PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d15_tessellation_shader PUBLIC util-core-4.1)
set_target_properties(d15_tessellation_shader PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d15_tessellation_shader 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vs=p4_shader_transform.glsl
  fs=p4_shader_color.glsl
  tc=p4_shader_tc.glsl
  te=p4_shader_te.glsl)
