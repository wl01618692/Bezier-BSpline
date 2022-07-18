# ---> demo 10 (camera transformation)
add_executable(d10_advanced_camera main.cpp)
target_include_directories(d10_advanced_camera PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d10_advanced_camera PUBLIC util-core-3.3)
set_target_properties(d10_advanced_camera PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d10_advanced_camera 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=shader_d10_vertex.glsl
  fragmentshader=shader_d10_fragment.glsl)
