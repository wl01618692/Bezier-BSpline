//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#include "shaders.h"
#include "util.hpp"
extern GLFWwindow* window;

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "arcball_camera.h"
extern ArcballCamera camera;
extern ArcballCamera light;
extern bool rotate_light;
extern bool spot_light;

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "framebuffer.h"
#include "geometry_triangle.h"
#include "pipeline.h"

void
update_arcball(ArcballCamera& ball, GLFWwindow* window, double xpos, double ypos);

void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

void
cursor(GLFWwindow* window, double xpos, double ypos);

bool
begin_gui();

void
end_gui();

void
init();

void
finalize();
