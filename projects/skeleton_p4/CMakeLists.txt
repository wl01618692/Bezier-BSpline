add_executable(run_p4 main.cpp helper.cpp helper.h gui.cpp gui.h)
target_include_directories(run_p4 PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(run_p4 PUBLIC util-core-4.1)
set_target_properties(run_p4 PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(run_p4 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=p4_shader_transform.glsl
  fragmentshader=p4_shader_color.glsl)
