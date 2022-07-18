# ---> demo 13 (shadow map)
add_library(d13_shadowmap_comm comm.cpp geometry_triangle.cpp)
target_include_directories(d13_shadowmap_comm PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d13_shadowmap_comm PUBLIC util-core-4.1)
set_target_properties(d13_shadowmap_comm PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d13_shadowmap_comm
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  depth_rtt_vs=shader_d13_depth_rtt.vs.glsl
  depth_rtt_fs=shader_d13_depth_rtt.fs.glsl
  shadow_mapping_vs=shader_d13_corrected.vs.glsl
  shadow_mapping_fs=shader_d13_corrected.fs.glsl
  shadow_mapping_simple_vs=shader_d13_simple.vs.glsl
  shadow_mapping_simple_fs=shader_d13_simple.fs.glsl
  passthrough_vs=shader_d13_passthrough.vs.glsl
  simple_texture_fs=shader_d13_simple_texture.fs.glsl)

add_executable(d13_shadowmap_simple main_simple.cpp)
target_link_libraries(d13_shadowmap_simple PUBLIC d13_shadowmap_comm)
set_target_properties(d13_shadowmap_simple PROPERTIES CXX_STANDARD 11)

add_executable(d13_shadowmap_corrected main_corrected.cpp)
target_link_libraries(d13_shadowmap_corrected PUBLIC d13_shadowmap_comm)
set_target_properties(d13_shadowmap_corrected PROPERTIES CXX_STANDARD 11)

foreach(f d13_uvmap.jpg)
  file(COPY ${f} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()
