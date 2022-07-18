//
// Created by ChiaYuan Chang on 11/30/20.
//

#ifndef ECS175_TEMPLATE_PROJECTS_SKELETON_P4_HELPER_H_
#define ECS175_TEMPLATE_PROJECTS_SKELETON_P4_HELPER_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "util.hpp"

// Define objects
struct Point {
  float x, y;
};

struct BezierCurve {
  // Output {c0, c1, c2, ...}
  std::vector<Point> C;

  // Input {b0, b1, b2 , ...}
  std::vector<Point> B;

  // Interval for time, t \in [0, 1]
  std::vector<float> domain;

  // Resolution for smoothness of curve
  int res = 50;

  // n  = number of control point - 1
  int n;

  // VBO object
  std::vector<float> g_vertex_buffer_lines;
  GLuint vertex_buffer_id_lines;

  // VBO object for Control points
  std::vector<float> b_vertex_buffer_lines;
  GLuint b_vertex_buffer_id_lines;
};

struct less_than_key {
  inline bool operator() (const Point& struct1, const Point& struct2) {
    if (struct1.x <= struct2.x)
      return true;
    return false;
  }
};

struct BSplineCurve{
  // Output {c0, c1, c2, ...}
  std::vector<Point> C;

  // Knots {u0, u1 , ...} where u0 < u1 < u2 < u3 < ... < u_{n + k}
  std::vector<float> U;

  // Control points {d0, d1, d2, ...} as input
  std::vector<Point> D;

  // Domain
  std::vector<float> domain;

  // Order
  int k;

  // n  = number of control point - 1
  // Note that n >= k - 1
  int n;

  // Resolution for smoothness of curve
  int res = 10;

  // VBO object for Bezier Curve
  std::vector<float> g_vertex_buffer_lines;
  GLuint vertex_buffer_id_lines;

  // VBO object for Control points
  std::vector<float> b_vertex_buffer_lines;
  GLuint b_vertex_buffer_id_lines;
};

// Read and output file function
void Readfile(int argc, char** argv);
void Outputfile(int argc, char** argv);
void ReadFileBezierCurve(const std::string& input);
void ReadFileBSplineCurve(const std::string& input);
void OutputFileBezierCurve(const std::string& input);
void OutputFileBSplineCurve(const std::string& input);

// VBO function
void CreateVBO();
void VBOSingleBezierCurve(BezierCurve& Bezier);
void VBOSingleBezierControlPoint(BezierCurve& Bezier);
void VBOSingleBSplineControlPoint(BSplineCurve& BSpline);
void VBOSingleBSplineCurve(BSplineCurve& BSpline);

// Bezier Curve method
void GenerateBezierCurve();
void DeCasteljau_algorithm(BezierCurve& B, float t);

// BSpline Curve method
void GenerateBSplineCurve();
void BSplineSetDomain(BSplineCurve& curve);
void DeBoor_algorithm(BSplineCurve& B, float u_bar);

// Calculate domain with current resolution
void SetResolution(BezierCurve& curve);

// Global variable declaration
extern std::vector<BSplineCurve> BSplineCurve_vec;
extern std::vector<BezierCurve> BezierCurve_vec;

#endif // ECS175_TEMPLATE_PROJECTS_SKELETON_P4_HELPER_H_
