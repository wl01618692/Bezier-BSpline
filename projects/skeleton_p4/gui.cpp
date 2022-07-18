//
// Created by ChiaYuan Chang on 12/6/20.
//

#include "gui.h"
#include "helper.h"
#include <algorithm>

// Detect if a point is included in the control point of a Bezier Curve
bool
NotIncluded(BezierCurve& curve, Point point)
{
  for (auto& item : curve.B)
    if (item.x == point.x && item.y == point.y)
      return false;
  return true;
}

// Detect if a point is included in the control point of a B Spline Curve
bool
NotIncluded(BSplineCurve& curve, Point point)
{
  for (auto& item : curve.D)
    if (item.x == point.x && item.y == point.y)
      return false;
  return true;
}

// Display menu
void
ShowMenu(bool* p_boolean, GLFWwindow* window)
{
  ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
  ImGui::Begin("Menu");
  // Module for Bezier Curve
  if (ImGui::CollapsingHeader("Bezier Curve"))
    BezierMenu(p_boolean, window);

  // Module for B-Spline Curve
  if (ImGui::CollapsingHeader("B-Spline Curve"))
    BSplineMenu(p_boolean, window);
  ImGui::End();
}

void
BezierMenu(bool* p_boolean, GLFWwindow* window)
{
  // Bezier Curve ID specification
  ImGui::Text("Bezier Curve ID");
  static int local_id = 0;
  ImGui::InputInt("Bezier Curve ID", &local_id);
  ImGui::Separator();

  // Add
  {
    ImGui::BulletText("Add");
    static float tx, ty = 0.0f;
    ImGui::DragFloat("Point.x##1", &tx, 0.1);
    ImGui::DragFloat("Point.y##2", &ty, 0.1);

    if (ImGui::Button("Add Front")) {
      if (NotIncluded(BezierCurve_vec.at(local_id), Point{ tx, ty })) {
        // Add value at front and clear all VBO for that Bezier Curve
        BezierCurve_vec.at(local_id).B.insert(BezierCurve_vec.at(local_id).B.begin() + 0, Point{ tx, ty });
        BezierCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
        BezierCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
        BezierCurve_vec.at(local_id).n += 1;

        // Now generate new Bezier Curve and create new VBO
        GenerateBezierCurve();
        VBOSingleBezierControlPoint(BezierCurve_vec.at(local_id));
        VBOSingleBezierCurve(BezierCurve_vec.at(local_id));
      }
      else {
        std::cerr << " This points is already included in the control points! Please enter again!" << std::endl;
      }
    }

    ImGui::SameLine();
    if (ImGui::Button("Add Back")) {
      // Add value at front and clear all VBO for that Bezier Curve
      BezierCurve_vec.at(local_id).B.insert(BezierCurve_vec.at(local_id).B.end(), Point{ tx, ty });
      BezierCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BezierCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
      BezierCurve_vec.at(local_id).n += 1;

      // Now generate new Bezier Curve and create new VBO
      GenerateBezierCurve();
      VBOSingleBezierControlPoint(BezierCurve_vec.at(local_id));
      VBOSingleBezierCurve(BezierCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Insert
  {
    ImGui::BulletText("Insert");
    static float px, py = 0.0f;
    ImGui::DragFloat("Point.x##3", &px, 0.1);
    ImGui::DragFloat("Point.y##4", &py, 0.1);
    ImGui::Text("Insert before control point");

    static int i_id = 0;
    ImGui::InputInt("control point", &i_id);

    if (ImGui::Button("Insert")) {
      // Add value at id and clear all VBO for that Bezier Curve
      BezierCurve_vec.at(local_id).B.insert(BezierCurve_vec.at(local_id).B.begin() + i_id, Point{ px, py });
      BezierCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BezierCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
      BezierCurve_vec.at(local_id).n += 1;

      // Now generate new Bezier Curve and create new VBO
      GenerateBezierCurve();
      VBOSingleBezierControlPoint(BezierCurve_vec.at(local_id));
      VBOSingleBezierCurve(BezierCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Delete
  {
    ImGui::BulletText("Delete");
    static int d_id = 0;
    ImGui::InputInt("Delete control point", &d_id);
    if (ImGui::Button("Delete")) {
      if (BezierCurve_vec.at(local_id).B.empty()) {
        // In this case, there is no control point for that curve, then we remove it
        BezierCurve_vec.erase(BezierCurve_vec.begin() + local_id);
      }
      else {
        // Remove value at id and clear all VBO for that Bezier Curve
        BezierCurve_vec.at(local_id).B.erase(BezierCurve_vec.at(local_id).B.begin() + d_id);
        BezierCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
        BezierCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
        BezierCurve_vec.at(local_id).n -= 1;

        // Now generate new Bezier Curve and create new VBO
        GenerateBezierCurve();
        VBOSingleBezierControlPoint(BezierCurve_vec.at(local_id));
        VBOSingleBezierCurve(BezierCurve_vec.at(local_id));
      }
    }
    ImGui::Separator();
  }

  // Modify
  {
    ImGui::BulletText("Modify");
    static int m_id = 0;
    ImGui::InputInt("Modify control point", &m_id);

    static float cx, cy = 0.0f;
    ImGui::DragFloat("Point.x##5", &cx, 0.1);
    ImGui::DragFloat("Point.y##6", &cy, 0.1);

    if (ImGui::Button("Modify")) {
      // Modify values and clear all VBO for that Bezier Curve
      BezierCurve_vec.at(local_id).B.at(m_id) = Point{ cx, cy };
      BezierCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BezierCurve_vec.at(local_id).b_vertex_buffer_lines.clear();

      // Now generate new Bezier Curve and create new VBO
      GenerateBezierCurve();
      VBOSingleBezierControlPoint(BezierCurve_vec.at(local_id));
      VBOSingleBezierCurve(BezierCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Set Resolution
  {
    ImGui::BulletText("Resolution");
    static int new_res = 2;
    ImGui::DragInt("Resolution##6", &new_res, 1, 2);

    if (ImGui::Button("Set")) {
      // Reset domain and clear all VBO for that Bezier Curve
      BezierCurve_vec.at(local_id).res = new_res;
      BezierCurve_vec.at(local_id).domain.clear();
      SetResolution(BezierCurve_vec.at(local_id));
      BezierCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BezierCurve_vec.at(local_id).b_vertex_buffer_lines.clear();

      // Now generate new Bezier Curve and create new VBO
      GenerateBezierCurve();
      VBOSingleBezierControlPoint(BezierCurve_vec.at(local_id));
      VBOSingleBezierCurve(BezierCurve_vec.at(local_id));
    }
  }
  ImGui::Separator();
}

void
BSplineMenu(bool* p_boolean, GLFWwindow* window)
{
  // BSpline Curve ID specification
  ImGui::Text("BSpline Curve ID");
  static int local_id = 0;
  ImGui::InputInt("BSpline Curve ID", &local_id);
  ImGui::Separator();

  // Add
  {
    ImGui::BulletText("Add");
    static float tx, ty = 0.0f;
    ImGui::DragFloat("Point.x##7", &tx, 0.1);
    ImGui::DragFloat("Point.y##8", &ty, 0.1);

    if (ImGui::Button("Add Front")) {
      if (NotIncluded(BSplineCurve_vec.at(local_id), Point{ tx, ty })) {
        // Add a value at front and clear all VBO for that BSpline Curve
        BSplineCurve_vec.at(local_id).D.insert(BSplineCurve_vec.at(local_id).D.begin(), Point{ tx, ty });
        BSplineCurve_vec.at(local_id).U.push_back(BSplineCurve_vec.at(local_id).k + BSplineCurve_vec.at(local_id).n +
                                                  1);
        std::sort(BSplineCurve_vec.at(local_id).U.begin(), BSplineCurve_vec.at(local_id).U.end());
        BSplineCurve_vec.at(local_id).domain.clear();
        BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
        BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
        BSplineCurve_vec.at(local_id).n += 1;

        // Now generate new BSpline Curve and create new VBO
        BSplineSetDomain(BSplineCurve_vec.at(local_id));
        GenerateBSplineCurve();
        VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
        VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
      }
      else {
        std::cout << " This points is already included in the control points!" << std::endl;
      }
    }

    ImGui::SameLine();
    if (ImGui::Button("Add Back")) {
      // Add values at back and clear all VBO for that BSpline Curve
      BSplineCurve_vec.at(local_id).D.insert(BSplineCurve_vec.at(local_id).D.end(), Point{ tx, ty });
      BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).n += 1;

      // Now generate new BSpline Curve and create new VBO
      GenerateBSplineCurve();
      VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
      VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Insert
  {
    ImGui::BulletText("Insert");
    static float px, py = 0.0f;
    ImGui::DragFloat("Point.x##9", &px, 0.1);
    ImGui::DragFloat("Point.y##10", &py, 0.1);
    ImGui::Text("Insert before control point");

    static int id = 0;
    ImGui::InputInt("Insert control point", &id);

    if (ImGui::Button("Insert")) {
      // Add values at id and clear all VBO for that BSpline Curve
      BSplineCurve_vec.at(local_id).D.insert(BSplineCurve_vec.at(local_id).D.begin() + id, Point{ px, py });
      BSplineCurve_vec.at(local_id).U.push_back(BSplineCurve_vec.at(local_id).k + BSplineCurve_vec.at(local_id).n + 1);
      std::sort(BSplineCurve_vec.at(local_id).U.begin(), BSplineCurve_vec.at(local_id).U.end());
      BSplineCurve_vec.at(local_id).domain.clear();
      BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).n += 1;

      // Now generate new BSpline Curve and create new VBO
      BSplineSetDomain(BSplineCurve_vec.at(local_id));
      GenerateBSplineCurve();
      VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
      VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Delete
  {
    ImGui::BulletText("Delete");
    static int id = 0;
    ImGui::InputInt("Remove control point", &id);
    if (ImGui::Button("Delete")) {
      if (BSplineCurve_vec.at(local_id).D.empty()) {
        // In this case, there is no control point for that curve, then we remove it
        BSplineCurve_vec.erase(BSplineCurve_vec.begin() + local_id);
      }
      else {
        // Remove value at id and clear all VBO for that BSpline Curve
        BSplineCurve_vec.at(local_id).D.erase(BSplineCurve_vec.at(local_id).D.begin() + id);
        BSplineCurve_vec.at(local_id).U.erase(BSplineCurve_vec.at(local_id).U.end() + id);
        BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
        BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
        BSplineCurve_vec.at(local_id).n -= 1;

        // Now generate new BSpline Curve and create new VBO
        GenerateBSplineCurve();
        VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
        VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
      }
    }
    ImGui::Separator();
  }

  // Modify
  {
    ImGui::BulletText("Modify");
    static int id = 0;
    ImGui::InputInt("Change control point", &id);
    static float cx, cy = 0.0f;
    ImGui::DragFloat("Point.x##11", &cx, 0.1);
    ImGui::DragFloat("Point.y##12", &cy, 0.1);
    if (ImGui::Button("Modify")) {
      // Modify values and clear all VBO for that BSpline Curve
      BSplineCurve_vec.at(local_id).D.at(id) = Point{ cx, cy };
      BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();

      // Now generate new BSpline Curve and create new VBO
      GenerateBSplineCurve();
      VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
      VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Set Resolution
  {
    ImGui::BulletText("Resolution");
    static int new_res = 2;
    ImGui::DragInt("New Resolution##13", &new_res, 1, 2);
    if (ImGui::Button("Set resolution")) {
      BSplineCurve_vec.at(local_id).res = new_res;
      BSplineCurve_vec.at(local_id).domain.clear();
      BSplineSetDomain(BSplineCurve_vec.at(local_id));
      BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();

      GenerateBSplineCurve();
      VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
      VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
    }
    ImGui::Separator();
  }

  // Change k
  {
    ImGui::BulletText("Order of B-spline (k)");
    static int new_k = 2;
    ImGui::DragInt("new k##14", &new_k, 1, 2);
    if (ImGui::Button("Set k")) {
      if (new_k <= 0) {
        std::cerr << "Invalid k, k must be an integer larger or equal to 1" << std::endl;
        return;
      }

      if (new_k - 1 > BSplineCurve_vec.at(local_id).n) {
        std::cerr << "Invalid k, k - 1 must be less than or equal to n" << std::endl;
        return;
      }

      BSplineCurve_vec.at(local_id).k = new_k;
      BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();
      BSplineCurve_vec.at(local_id).domain.clear();
      BSplineSetDomain(BSplineCurve_vec.at(local_id));

      GenerateBSplineCurve();
      VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
      VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
      ImGui::Separator();
    }

    // Change knot values
    {
      ImGui::BulletText("Change knot values");
      static int knot_pos = 0;
      ImGui::DragInt("Index for knot##15", &knot_pos, 1, 0);

      static float knot_value = 0.0f;
      ImGui::DragFloat("New knot value##16", &knot_value, 0.1);

      if (ImGui::Button("Set knot values")) {
        BSplineCurve_vec.at(local_id).U.at(knot_pos) = knot_value;
        std::sort(BSplineCurve_vec.at(local_id).U.begin(), BSplineCurve_vec.at(local_id).U.end());
        BSplineCurve_vec.at(local_id).domain.clear();
        BSplineSetDomain(BSplineCurve_vec.at(local_id));
        BSplineCurve_vec.at(local_id).g_vertex_buffer_lines.clear();
        BSplineCurve_vec.at(local_id).b_vertex_buffer_lines.clear();

        GenerateBSplineCurve();
        VBOSingleBSplineControlPoint(BSplineCurve_vec.at(local_id));
        VBOSingleBSplineCurve(BSplineCurve_vec.at(local_id));
      }
      ImGui::Separator();
    }
  }
}
