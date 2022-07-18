//
// Created by ChiaYuan Chang on 12/6/20.
//

#ifndef ECS175_TEMPLATE_PROJECTS_SKELETON_P4_GUI_H_
#define ECS175_TEMPLATE_PROJECTS_SKELETON_P4_GUI_H_
// Include imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

// Declaration
struct BSplineCurve;
struct BezierCurve;

// Menu function
void ShowMenu(bool* p_boolean, GLFWwindow* window);
void BSplineMenu(bool* p_boolean, GLFWwindow* window);
void BezierMenu(bool* p_boolean, GLFWwindow* window);

// Global variable declaration
extern std::vector<BSplineCurve> BSplineCurve_vec;
extern std::vector<BezierCurve> BezierCurve_vec;

#endif // ECS175_TEMPLATE_PROJECTS_SKELETON_P4_GUI_H_
