# ---> demo 9 (loading OBJ file, rendering using vertex indexing)
add_executable(d9_geometries
  geometry_triangle.cpp 
  main.cpp)
target_include_directories(d9_geometries PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d9_geometries PUBLIC util-core-3.3)
set_target_properties(d9_geometries PROPERTIES CXX_STANDARD 11)
target_add_embeded_shaders(d9_geometries 
  OUTPUT_NAME ${CMAKE_CURRENT_BINARY_DIR}/shaders.h 
  SHADERS
  vertexshader=shader_d9_vertex.glsl
  fragmentshader=shader_d9_fragment.glsl)
