# ---> demo 3 (simple shaders + loading from file)
add_executable(d3_simple_shader_file main_file.cpp)
target_include_directories(d3_simple_shader_file PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d3_simple_shader_file PUBLIC util-core-3.3)
set_target_properties(d3_simple_shader_file PROPERTIES CXX_STANDARD 11)
message(STATUS "Copying shader to build directory [d3_simple_shader_file]")
foreach(f shader_d3_vertex.glsl
          shader_d3_fragment.glsl)
  file(COPY ${f} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# ---> demo 3 (simple shaders + embeded into C)
add_executable(d3_simple_shader_embeded main_embeded.cpp)
target_include_directories(d3_simple_shader_embeded PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d3_simple_shader_embeded PUBLIC util-core-3.3)
set_target_properties(d3_simple_shader_embeded PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d3_simple_shader_embeded 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=shader_d3_vertex.glsl
  fragmentshader=shader_d3_fragment.glsl)
