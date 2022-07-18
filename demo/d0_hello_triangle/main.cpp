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

//------------------------------------------------------------------------
// setup callbacks
//------------------------------------------------------------------------

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
    screen_shot(window, "d0.jpg");
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

static void
resize(GLFWwindow* window, int width, int height)
{
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void
draw(GLFWwindow* window)
{
  float ratio;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  ratio = width / (float)height;
  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
  glBegin(GL_TRIANGLES);
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-0.6f, -0.4f, 0.f);
  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(0.6f, -0.4f, 0.f);
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(0.f, 0.6f, 0.f);
  glEnd();
}

//---------------------------------------------------------------------------------------

int
main(const int argc, const char** argv)
{
  printf("In this demo, you can learn how to create\n"
         "an graphics window and draw simple shapes\n"
         "on it using the legacy OpenGL API.\n");

  int width = 800, height = 600;

  // Initialize GLFW
  glfwSetErrorCallback(error);
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  // Provide Window Hint
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // OpenGL Setup
  GLFWwindow* window = NULL;
  window = glfwCreateWindow(width, height, "ECS 175 Demo", NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  // Ready
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // Load GLAD symbols
  int err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;
  if (err) {
    throw std::runtime_error("Failed to initialize OpenGL loader!");
  }

  // Callback
  glfwSetKeyCallback(window, keyboard);
  glfwSetWindowSizeCallback(window, resize);
  glfwSetCursorPosCallback(window, cursor);

  // Execute
  while (!glfwWindowShouldClose(window)) {
    draw(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Exit
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
