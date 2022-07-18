add_executable(d7_point_in_polygon main.cpp)
target_include_directories(d7_point_in_polygon PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(d7_point_in_polygon PUBLIC util-compatible ${gl_libs})
set_target_properties(d7_point_in_polygon PROPERTIES CXX_STANDARD 11) 
