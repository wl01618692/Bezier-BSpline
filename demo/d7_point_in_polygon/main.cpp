//===========================================================================//
//                                                                           //
// Copyright(c) 2018 Qi Wu (Wilson)                                          //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#include "util.hpp"

#include <iostream>
#include <string>
#include <vector>

float grid_width = 10, grid_height = 10;

struct Point {
  float x, y;
};

std::vector<std::vector<Point>> polygons = {
  std::vector<Point>{ Point{ 2.0, 2.0 }, Point{ 4.0, 2.0 }, Point{ 4.0, 4.0 }, Point{ 2.0, 4.0 } },
  std::vector<Point>{ Point{ 6.0, 6.0 }, Point{ 8.0, 8.0 }, Point{ 8.0, 6.0 } }
};

int current = 0; // current polygon

// Point in Polygon: The Crossing Number
bool
cn_PnPoly(Point P, const Point* V, int n)
{
  int cn = 0; // the crossing number counter
  // loop through all edges of the polygon
  for (int i = 0; i < n - 1; ++i) {
    auto& ps = V[i];
    auto& pe = V[i + 1];
    // horizontal edges are excluded
    const bool horizontal = pe.y == ps.y;
    if (!horizontal) {
      const bool upward = pe.y > ps.y;
      // an upward edge includes its starting endpoint, and excludes its final endpoint
      const bool rule1 = upward && (ps.y <= P.y) && (P.y < pe.y);
      // a downward edge excludes its starting endpoint, and includes its final endpoint
      const bool rule2 = (!upward) && (ps.y > P.y) && (P.y >= pe.y);
      if (rule1 || rule2) {
        const float x_intersect = ps.x + (pe.x - ps.x) / (pe.y - ps.y) * (P.y - ps.y);
        // the edge-ray intersection point must be strictly right of the point P
        if (P.x < x_intersect)
          ++cn; // a valid crossing to the right of P.x
      }
    }
  }
  return (cn & 1); // 0 if even (out), and 1 if odd (in)
}

void
CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  int left_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  int right_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

  Point P{ float(xpos / width * grid_width), float((1.f - ypos / height) * grid_height) };

  if (P.x > 0 && P.x < grid_width && P.y > 0 && P.y < grid_height) {
    for (int i = 0; i < polygons.size(); ++i) {
      bool b = cn_PnPoly(P, polygons[i].data(), polygons[i].size());
      if (b)
        current = i;
    }
  }

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

void
draw(GLFWwindow* window)
{
  // Reset the viewport, here we need to use the framebuffer size
  int frame_width, frame_height;
  glfwGetFramebufferSize(window, &frame_width, &frame_height);
  glViewport(0, 0, frame_width, frame_height);

  int width, height;
  glfwGetWindowSize(window, &width, &height);
  float ratio = width / (float)height;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);

  glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const float pixel = width / (float)grid_width;
  glPointSize(pixel);

  const float sx = 1.f / grid_width * width, sy = 1.f / grid_height * height;

  int i = 0;
  for (auto& p : polygons) {
    // build matrix
    glMatrixMode(GL_MODELVIEW); // clear the modelview matrix
    glLoadIdentity();

    // build polygon
    glBegin(GL_POLYGON);
    {
      if (i == current) // high light the selected polygon
        glColor3f(1.f, 0.f, 0.f);
      else
        glColor3f(1.f, 1.f, 1.f);
      // specify vertices in the object space
      for (auto& k : p)
        glVertex3f(k.x * sx, k.y * sy, 0.f);
    }
    glEnd();
    ++i;
  }
}

int
main(const int argc, const char** argv)
{
  GLFWwindow* window = NULL;

  // Setup an OpenGL Window
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  // Provide Window Hint
  glfwWindowHint(GLFW_DEPTH_BITS, 16);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(600, 600, "ECS 175 Demo", NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window);
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
    throw std::runtime_error("Failed to initialize OpenGL loader!");
  }

  glfwSwapInterval(1);
  glfwSetCursorPosCallback(window, CursorPositionCallback);

  // Execute
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
    draw(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Exit
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
