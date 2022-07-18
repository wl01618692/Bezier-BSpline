//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

// Include standard headers
#include "shaders.h"
#include "util.hpp"
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

int
main(void)
{
  // Initialise GLFW
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "ECS 175 Demo (Press 'n'...)", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    throw std::runtime_error("Failed to open GLFW window. If you have a GPU that is "
                             "not 3.3 compatible, try a lower OpenGL version.");
  }

  glfwMakeContextCurrent(window);

  // Load GLAD symbols
  int err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;
  if (err) {
    throw std::runtime_error("Failed to initialize OpenGL loader!");
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  // Create and compile our GLSL program from the shaders
  GLuint program_id = load_program_from_embedding(vs, vs_size, fs, fs_size, NULL, 0, tc, tc_size, te, te_size);

  // Get a handle for our "MVP" uniform
  GLuint matrix_id = glGetUniformLocation(program_id, "Matrix");
  glm::mat4 matrix = { 1.086396,  -0.993682, -0.687368, -0.685994, 0.000000, 2.070171, -0.515526, -0.514496,
                       -1.448528, -0.745262, -0.515526, -0.514496, 0.000000, 0.000000, 5.642426,  5.830953 };

  /* you compute your curves here */
  static const GLfloat g_patch[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f };

  GLuint vbo_patch;
  glGenBuffers(1, &vbo_patch);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_patch);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_patch), g_patch, GL_STATIC_DRAW);

  do {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(program_id);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &matrix[0][0]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_patch);

    glVertexAttribPointer(0, // attribute. No particular reason for 0, but must
                             // match the layout in the shader.
                          3, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0, // stride
                          (void*)0 // array buffer offset
    );

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArrays(GL_PATCHES, 0, 4);

    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  // Cleanup VBO and shader
  glDeleteBuffers(1, &vbo_patch);
  glDeleteProgram(program_id);
  glDeleteVertexArrays(1, &vertex_array_id);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
