//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

// In this part the student will setup an OpenGL window
#include "util.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>

//---------------------------------------------------------------------------------------
// TODO setup callbacks
//---------------------------------------------------------------------------------------

static void
error(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    // take a screen shot
    screen_shot(window, "d1.jpg");
    // close window
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

static void
cursor(GLFWwindow* window, double xpos, double ypos)
{
  int left_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  int right_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
  // left click
  if (left_state == GLFW_PRESS) {
  }
  else {
  }

  // right click
  if (right_state == GLFW_PRESS) {
  }
  else {
  }
}

/* new window size */
static void
resize(GLFWwindow* window, int width, int height)
{
  GLfloat h = (GLfloat)height / (GLfloat)width;
  GLfloat xmax, znear, zfar;

  znear = 5.0f;
  zfar = 30.0f;
  xmax = znear * 0.5f;

  glViewport(0, 0, (GLint)width, (GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-xmax, xmax, -xmax * h, xmax * h, znear, zfar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -20.0);
}

//---------------------------------------------------------------------------------------

void
DrawInit(GLFWwindow* window, int width, int height);

void
DrawCall(GLFWwindow* window);

/* update animation parameters */
void
Animate(void);

//---------------------------------------------------------------------------------------

int
main(const int argc, const char** argv)
{
  printf("In this demo, you can learn how to create\n"
         "real-time animations using the legacy\n"
         "OpenGL API.\n");

  GLFWwindow* window = NULL;

  int width = 300, height = 300;

  // Setup an OpenGL Window
  {
    glfwSetErrorCallback(error);
    if (!glfwInit()) {
      exit(EXIT_FAILURE);
    }

    // Provide Window Hint
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);

    window = glfwCreateWindow(width, height, "ECS 175 Demo", NULL, NULL);
    if (!window) {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, cursor);
    glfwSetFramebufferSizeCallback(window, resize);

    glfwMakeContextCurrent(window);
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
      throw std::runtime_error("Failed to initialize OpenGL loader!");
    }

    glfwSwapInterval(1);
  }

  // Execute
  glfwGetFramebufferSize(window, &width, &height);
  resize(window, width, height);
  DrawInit(window, width, height);
  while (!glfwWindowShouldClose(window)) {
    Animate();
    DrawCall(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Exit
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
