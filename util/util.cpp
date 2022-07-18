//===========================================================================//
//                                                                           //
// Copyright(c) 2018 Qi Wu (Wilson)                                          //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#include "util.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// trying this obj loader https://github.com/syoyo/tinyobjloader
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

#include <chrono>
#include <fstream>
#include <string>

//---------------------------------------------------------------------------------------
// error check helper from EPFL ICG class
static inline const char*
ErrorString(GLenum error)
{
  const char* msg;
  switch (error) {
#define Case(Token) \
  case Token:       \
    msg = #Token;   \
    break;
    Case(GL_INVALID_ENUM);
    Case(GL_INVALID_VALUE);
    Case(GL_INVALID_OPERATION);
    Case(GL_INVALID_FRAMEBUFFER_OPERATION);
    Case(GL_NO_ERROR);
    Case(GL_OUT_OF_MEMORY);
#undef Case
  }
  return msg;
}

void
_glCheckError(const char* file, int line, const char* comment)
{
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "ERROR: %s (file %s, line %i: %s).\n", comment, file, line, ErrorString(error));
  }
}

//---------------------------------------------------------------------------------------

void
save_jpg(const std::string& fname, std::vector<uint8_t>& fb, int w, int h)
{
  const size_t nchannel = fb.size() / ((size_t)w * (size_t)h);
  if (nchannel == 3) {
    stbi_write_jpg(fname.c_str(), w, h, 3, fb.data(), 100);
  }
  else if (nchannel == 4) {
    const int& width = w;
    const int& height = h;
    uint8_t* pixels = new uint8_t[width * height * 3];
    int index = 0;
    for (int j = height - 1; j >= 0; --j) {
      for (int i = 0; i < width; ++i) {
        int ir = int(fb[4 * (i + j * width) + 0]);
        int ig = int(fb[4 * (i + j * width) + 1]);
        int ib = int(fb[4 * (i + j * width) + 2]);
        pixels[index++] = ir;
        pixels[index++] = ig;
        pixels[index++] = ib;
      }
    }
    stbi_write_jpg(fname.c_str(), width, height, 3, pixels, 100);
    delete[] pixels;
  }
  else {
    throw std::runtime_error("Unknown image type");
  }
}

void
read_frame(GLFWwindow* window, std::vector<uint8_t>& buffer, int w, int h)
{
  const size_t nchannel = buffer.size() / ((size_t)w * (size_t)h);
  assert(nchannel == 3);
  // reading from the default framebuffer
  glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, &(buffer[0]));
  check_error_gl("Save a frame");
}

void
screen_shot(GLFWwindow* window, const std::string& fname)
{
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  std::vector<uint8_t> fb(size_t(width) * size_t(height) * size_t(3));
  read_frame(window, fb, width, height);
  save_jpg(fname, fb, width, height);
}

GLuint
load_texture_from_file(const char* imagepath)
{
  printf("Reading image %s\n", imagepath);

  int width, height, channels;

  // Actual RGB data
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(imagepath, &width, &height, &channels, STBI_rgb);

  // Create one OpenGL texture
  GLuint textureID;
  glGenTextures(1, &textureID);

  // "Bind" the newly created texture : all future texture functions will modify
  // this texture
  glBindTexture(GL_TEXTURE_2D, textureID);

  // Give the image to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  // OpenGL has now copied the data. Free our own version
  delete[] data;

  // Poor filtering, or ...
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // ... nice trilinear filtering ...
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  // ... which requires mipmaps. Generate them automatically.
  glGenerateMipmap(GL_TEXTURE_2D);

  // Return the ID of the texture we just created
  return textureID;
}

//---------------------------------------------------------------------------------------

void
check_shader_compilation_log(GLuint shader, const std::string& fname)
{
  GLint isCompiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
    // Provide the infolog in whatever manor you deem best.
    // Exit with failure.
    glDeleteShader(shader); // Don't leak the shader.
    // show the message
    std::cerr << "compilation error for shader: " << fname << std::endl << errorLog.data() << std::endl;
  }
}

void
attach_shader(GLuint program, GLuint type, const char* ptr, const std::string& msg)
{
  GLuint shader = glCreateShader(type);
  {
    glShaderSource(shader, 1, &ptr, NULL);
    glCompileShader(shader);
    check_shader_compilation_log(shader, msg.c_str());
    check_error_gl(msg.c_str());
  }
  glAttachShader(program, shader);
  check_error_gl("Compile Shaders: Attach");
}

void
attach_shader(GLuint program, GLuint type, const void* _data, size_t size, const std::string& msg)
{
  const char* data = (const char*)_data;
  std::string str = "";
  for (int i = 0; i < size; ++i) {
    str += data[i];
  }
  const char* ptr = str.c_str();
  // const char* ptr = str.c_str();
  attach_shader(program, type, ptr, msg);
}

static const char*
ReadShaderFile(const char* fname)
{
  std::ifstream file(fname, std::ios::binary | std::ios::ate | std::ios::in);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  char* buffer = new char[size + 1];
  buffer[size] = '\0';
  if (!file.read(const_cast<char*>(buffer), size)) {
    fprintf(stderr, "Error: Cannot read file %s\n", fname);
    exit(-1);
  }
  return buffer;
}

#if !defined(ENABLE_OPENGL_COMPATIBLE)
GLuint
load_program_from_files(const char* vshader_fname, const char* fshader_fname)
{
  fprintf(stdout, "[shader] reading vertex shader file %s\n", vshader_fname);
  fprintf(stdout, "[shader] reading fragment shader file %s\n", fshader_fname);
  // Create program
  GLuint program = glCreateProgram();
  if (glCreateProgram == 0)
    throw std::runtime_error("wrong program");
  // Vertex shader
  const char* vshader_text = ReadShaderFile(vshader_fname);
  attach_shader(program, GL_VERTEX_SHADER, vshader_text, "Compile Vertex Shader");
  // Fragment shader
  const char* fshader_text = ReadShaderFile(fshader_fname);
  attach_shader(program, GL_FRAGMENT_SHADER, fshader_text, "Compile Fragment Shader");
  // Link shaders
  glLinkProgram(program);
  check_error_gl("Compile Shaders: Link");
  glUseProgram(program);
  check_error_gl("Compile Shaders: Final");
  return program;
}
#endif

#if defined(ENABLE_OPENGL_CORE_3_3)
GLuint
load_program_from_embedding(const void* _vshader_text,
                            long int vshader_size,
                            const void* _fshader_text,
                            long int fshader_size,
                            const void* _gshader_text,
                            long int gshader_size)
{
  // Create program
  GLuint program = glCreateProgram();
  if (glCreateProgram == 0)
    throw std::runtime_error("wrong program");
  // Vertex shader
  attach_shader(program, GL_VERTEX_SHADER, _vshader_text, vshader_size, "Compile Vertex Shader");
  // Fragment shader
  attach_shader(program, GL_FRAGMENT_SHADER, _fshader_text, fshader_size, "Compile Fragment Shader");
  // Geometry shader
  if (_gshader_text)
    attach_shader(program, GL_GEOMETRY_SHADER, _gshader_text, gshader_size, "Compile Geometry Shader");
  // Link shaders
  glLinkProgram(program);
  check_error_gl("Compile Shaders: Link");
  glUseProgram(program);
  check_error_gl("Compile Shaders: Final");
  return program;
}
#endif

#if defined(ENABLE_OPENGL_CORE_4_1)
GLuint
load_program_from_embedding(const void* _vshader_text,
                            long int vshader_size,
                            const void* _fshader_text,
                            long int fshader_size,
                            const void* _gshader_text,
                            long int gshader_size,
                            const void* _tcshader_text,
                            long int tcshader_size,
                            const void* _teshader_text,
                            long int teshader_size)
{
  // Create program
  GLuint program = glCreateProgram();
  if (glCreateProgram == 0)
    throw std::runtime_error("wrong program");
  // Vertex shader
  attach_shader(program, GL_VERTEX_SHADER, _vshader_text, vshader_size, "Compile Vertex Shader");
  // Fragment shader
  attach_shader(program, GL_FRAGMENT_SHADER, _fshader_text, fshader_size, "Compile Fragment Shader");
  // Geometry shader
  if (_gshader_text)
    attach_shader(program, GL_GEOMETRY_SHADER, _gshader_text, gshader_size, "Compile Geometry Shader");
  // Tessellation shaders
  if (_tcshader_text)
    attach_shader(
      program, GL_TESS_CONTROL_SHADER, _tcshader_text, tcshader_size, "Compile Tessellation Control Shader");
  if (_teshader_text)
    attach_shader(
      program, GL_TESS_EVALUATION_SHADER, _teshader_text, teshader_size, "Compile Tessellation Evaluation Shader");
  // Link shaders
  glLinkProgram(program);
  check_error_gl("Compile Shaders: Link");
  glUseProgram(program);
  check_error_gl("Compile Shaders: Final");
  return program;
}
#endif

float
get_framerate()
{
  static float fps = 0.0f; // measure frame rate
  static size_t frames = 0;
  static auto start = std::chrono::system_clock::now();
  ++frames;
  if (frames % 10 == 0 || frames == 1) { // dont update this too frequently
    std::chrono::duration<double> es = std::chrono::system_clock::now() - start;
    fps = frames / es.count();
  }
  return fps;
}
