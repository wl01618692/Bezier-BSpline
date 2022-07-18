//===========================================================================//
//                                                                           //
// Copyright(c) 2018 Qi Wu (Wilson)                                          //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#pragma once

#ifdef ENABLE_OPENGL_COMPATIBLE
#ifdef ENABLE_OPENGL_CORE_3_3
#error "Legacy OpenGL is selected, but libraries compiled in OpenGL 3.3 are linked"
#endif
#ifdef ENABLE_OPENGL_CORE_4_1
#error "Legacy OpenGL is selected, but libraries compiled in OpenGL 4.1 are linked"
#endif
#endif

#ifdef ENABLE_OPENGL_CORE_3_3
#ifdef ENABLE_OPENGL_COMPATIBLE
#error "OpenGL 3.3 is selected, but libraries compiled in Legacy OpenGL are linked"
#endif
#ifdef ENABLE_OPENGL_CORE_4_1
#error "OpenGL 3.3 is selected, but libraries compiled in OpenGL 4.1 are linked"
#endif
#endif

#ifdef ENABLE_OPENGL_CORE_4_1
#ifdef ENABLE_OPENGL_COMPATIBLE
#error "OpenGL 4.1 is selected, but libraries compiled in Legacy OpenGL are linked"
#endif
#ifdef ENABLE_OPENGL_CORE_3_3
#error "OpenGL 4.1 is selected, but libraries compiled in OpenGL 3.3 are linked"
#endif
#endif

#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
// it is necessary to include glad before glfw
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <vector>

void
_glCheckError(const char* file, int line, const char* comment);

#ifndef NDEBUG
#define check_error_gl(x) _glCheckError(__FILE__, __LINE__, x)
#else
#define check_error_gl(x) ((void)0)
#endif

#ifndef NDEBUG
#define ASSERT(condition, message)                                                                                \
  do {                                                                                                            \
    if (!(condition)) {                                                                                           \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message \
                << std::endl;                                                                                     \
      std::terminate();                                                                                           \
    }                                                                                                             \
  } while (false)
#define WARN(condition, message)                                                                                  \
  do {                                                                                                            \
    if (!(condition)) {                                                                                           \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message \
                << std::endl;                                                                                     \
    }                                                                                                             \
  } while (false)
#else
#define ASSERT(condition, message) \
  do {                             \
  } while (false)
#define WARN(condition, message) \
  do {                           \
  } while (false)
#endif

void
read_frame(GLFWwindow* window, std::vector<uint8_t>& buffer, int w, int h);

void
save_jpg(const std::string& fname, std::vector<uint8_t>& fb, int w, int h);

void
screen_shot(GLFWwindow* window, const std::string& fname);

GLuint
load_texture_from_file(const char* imagepath); // Load a texture from a file

#if !defined(ENABLE_OPENGL_COMPATIBLE)
GLuint
load_program_from_files(const char* vshader_fname, const char* fshader_fname);
#endif

#if defined(ENABLE_OPENGL_CORE_3_3)
GLuint
load_program_from_embedding(const void* _vshader_text,
                            long int vshader_size,
                            const void* _fshader_text,
                            long int fshader_size,
                            const void* _gshader_text = NULL,
                            long int gshader_size = 0);
#endif

#if defined(ENABLE_OPENGL_CORE_4_1)
GLuint
load_program_from_embedding(const void* _vshader_text,
                            long int vshader_size,
                            const void* _fshader_text,
                            long int fshader_size,
                            const void* _gshader_text = NULL,
                            long int gshader_size = 0,
                            const void* _tcshader_text = NULL,
                            long int tcshader_size = 0,
                            const void* _teshader_text = NULL,
                            long int teshader_size = 0);
#endif

float
get_framerate();
