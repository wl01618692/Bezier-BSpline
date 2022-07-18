# ---> demo 6 (drawing a textured cube)
add_executable(d6_texture_cube main.cpp)
target_include_directories(d6_texture_cube PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d6_texture_cube PUBLIC util-core-3.3)
set_target_properties(d6_texture_cube PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d6_texture_cube
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h
  SHADERS
  vertexshader=shader_d6_vertex.glsl
  fragmentshader=shader_d6_fragment.glsl)
foreach(f d6_uvtemplate.bmp)
  file(COPY ${f} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()
