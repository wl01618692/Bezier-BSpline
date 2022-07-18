# Install script for directory: /Users/chiayuanchang/Desktop/p4/demo

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d0_hello_triangle/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d1_glgears/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d2_imgui/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d5_colored_cube/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d6_texture_cube/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d7_point_in_polygon/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d9_geometries/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d10_advanced_camera/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d11_render_to_texture/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d12_reordering/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d13_shadowmap/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d14_geometry_shader/cmake_install.cmake")
  include("/Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d15_tessellation_shader/cmake_install.cmake")

endif()

