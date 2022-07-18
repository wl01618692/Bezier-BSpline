# ---> demo 0 (a rotating triangle)
add_executable(d0_hello_triangle 
  main.cpp)
target_link_libraries(d0_hello_triangle PUBLIC util-compatible)
set_target_properties(d0_hello_triangle PROPERTIES CXX_STANDARD 11)
