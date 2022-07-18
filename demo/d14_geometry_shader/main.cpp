//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#include "shaders.h"
#include "util.hpp"

#include <iostream>

void
framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Reference https://www.khronos.org/opengl/wiki/Geometry_Shader

int
main()
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ECS 175 - Shadows", NULL, NULL);
  if (window == NULL) {
    std::runtime_error("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

  // build and compile shaders
  // -------------------------
  GLuint program_id = load_program_from_embedding(vs, vs_size, fs, fs_size, gs, gs_size);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float points[] = {
    /* aPos */ -0.5f, 0.5f,  /* aColor */ 1.0f, 0.0f, 0.0f, // top-left
    /* aPos */ 0.5f,  0.5f,  /* aColor */ 0.0f, 1.0f, 0.0f, // top-right
    /* aPos */ 0.5f,  -0.5f, /* aColor */ 0.0f, 0.0f, 1.0f, // bottom-right
    /* aPos */ -0.5f, -0.5f, /* aColor */ 1.0f, 1.0f, 0.0f // bottom-left
  };

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  GLuint vertex_buffer_id;
  glGenBuffers(1, &vertex_buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, // The attribute we want to configure
                        2, // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized?
                        5 * sizeof(float), // stride
                        (void*)0 // array buffer offset
  );

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, // The attribute we want to configure
                        3, // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized?
                        5 * sizeof(float), // stride
                        (void*)(2 * sizeof(float)) // array buffer offset
  );

  glBindVertexArray(0);

  // render loop
  // -----------
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw points
    glUseProgram(program_id);
    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_POINTS, 0, 4);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &vertex_array_id);
  glDeleteBuffers(1, &vertex_buffer_id);

  glfwTerminate();
  return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void
framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
