//
// Created by ChiaYuan Chang on 11/30/20.
//

#include "helper.h"
template<typename T>
T SafeRead(std::ifstream& is)
{
  T ret;
  is >> ret;
  auto rdstate = is.rdstate();
  if ((rdstate & std::ifstream::eofbit) != 0)
    throw std::runtime_error("End-of-File reached on input operation");
  if ((rdstate & std::ifstream::failbit) != 0)
    throw std::runtime_error("Logical error on i/o operation");
  if ((rdstate & std::ifstream::badbit) != 0)
    throw std::runtime_error("Read/writing error on i/o operation");
  return ret;
}

void
Readfile(int argc, char** argv)
{
  std::string input1 = argv[1];
  for (auto& item : input1) {
    item = tolower(item);
  }

  if (argc < 2 || argc > 4)
    std::cerr << "Invalid number of command line arguments" << std::endl;

  if (input1 == "bspline") {
    ReadFileBSplineCurve(argv[2]);
  }
  else if (input1 == "bezier") {
    ReadFileBezierCurve(argv[2]);
  }
  else if (input1 == "both") {
    ReadFileBezierCurve(argv[2]);
    ReadFileBSplineCurve(argv[3]);
  }
  else {
    std::cerr << "Invalid command line arguments" << std::endl;
  }
}

void
ReadFileBezierCurve(const std::string& input)
{
  std::ifstream file(input);
  if (!file.is_open())
    throw std::runtime_error("cannot open input: " + input);

  int n = SafeRead<int>(file);
  std::cout << "There are " << n << " Bezier curve" << std::endl;

  BezierCurve_vec.resize(n);

  for (auto& p : BezierCurve_vec) {
    int m = SafeRead<int>(file);
    p.n = m - 1;
    for (auto i = 0; i < m; ++i) {
      float x = SafeRead<float>(file), y = SafeRead<float>(file);
      p.B.push_back(Point{ x, y });
    }
  }
  file.close();

  // Initialize domain vector for each curve
  for (auto& BezierCurve : BezierCurve_vec) {
    SetResolution(BezierCurve);
  }
}

void
ReadFileBSplineCurve(const std::string& input)
{
  std::ifstream file(input);
  if (!file.is_open())
    throw std::runtime_error("cannot open input: " + input);

  int n = SafeRead<int>(file);
  std::cout << "There are " << n << " B-spline curve" << std::endl;

  BSplineCurve_vec.resize(n);

  for (auto& p : BSplineCurve_vec) {
    int m = SafeRead<int>(file);
    p.k = m;
    int k = SafeRead<int>(file);
    p.n = k - 1;
    for (auto i = 0; i < k; ++i) {
      float x = SafeRead<float>(file), y = SafeRead<float>(file);
      p.D.push_back(Point{ x, y });
    }
    for (auto i = 0; i < k + m; ++i) {
      float x = SafeRead<float>(file);
      p.U.push_back(x);
    }
  }
  file.close();

  // Initialize domain vector for each curve
  for (auto& BSplineCurve : BSplineCurve_vec) {
    BSplineSetDomain(BSplineCurve);
  }
}

void
Outputfile(int argc, char** argv)
{ // Output file
  std::string input1 = argv[1];
  auto temp = input1;
  for (auto& item : temp) {
    item = tolower(item);
  }

  if (temp == "bspline") {
    OutputFileBSplineCurve(argv[2]);
  }
  else if (temp == "bezier") {
    OutputFileBezierCurve(argv[2]);
  }
  else if (temp == "both") {
    OutputFileBezierCurve(argv[2]);
    OutputFileBSplineCurve(argv[3]);
  }
}

void
OutputFileBezierCurve(const std::string& input)
{
  std::ofstream file(input, std::ofstream::trunc);
  // Number of polygon
  file << BezierCurve_vec.size() << std::endl;
  file << std::endl;
  for (auto& p : BezierCurve_vec) {
    file << p.B.size() << std::endl;
    for (auto& point : p.B) {
      file << point.x << " " << point.y << std::endl;
    }
    file << std::endl;
  }
  file.close();
}


void
OutputFileBSplineCurve(const std::string& input)
{
  std::ofstream file(input, std::ofstream::trunc);
  // Number of polygon
  file << BSplineCurve_vec.size() << std::endl;
  file << std::endl;
  for (auto& p : BSplineCurve_vec) {
    file << p.k << std::endl;
    file << p.D.size() << std::endl;
    for (auto& point : p.D) {
      file << point.x << " " << point.y << std::endl;
    }
    for (auto& point : p.U) {
      file << point << std::endl;
    }
    file << std::endl;
  }
  file.close();
}

void
SetResolution(BezierCurve& curve)
{
  // Initialize domain vector for a curve
  curve.domain.resize(curve.res + 1);
  double t = 0;
  double size = 1.0f / curve.res;
  for (int kI = 0; kI <= curve.res; ++kI) {
    curve.domain.at(kI) = t;
    t += size;
  }
}

void
BSplineSetDomain(BSplineCurve& BSplineCurve)
{
  auto left = BSplineCurve.U.at(BSplineCurve.k - 1);
  auto right = BSplineCurve.U.at(BSplineCurve.n + 1);

  BSplineCurve.domain.resize((BSplineCurve.res) * (BSplineCurve.n + 1 - (BSplineCurve.k - 1)) + 1);
  float t = left;

  for (int i = BSplineCurve.k - 1, kJ = 0; i < BSplineCurve.n + 1; ++i) {
    if (i == BSplineCurve.n + 1) {
      break;
    }

    float size = (BSplineCurve.U.at(i + 1) - BSplineCurve.U.at(i)) / (BSplineCurve.res);
    for (int kI = 0; kI <= BSplineCurve.res; ++kI, ++kJ) {
      if (kJ == BSplineCurve.domain.size())
        break;

      BSplineCurve.domain.at(kJ) = t;
      t += size;
    }
  }
}

void
CreateVBO()
{
  GenerateBSplineCurve();
  GenerateBezierCurve();

  // Generate VBO for Bezier Curve
  for (auto& Bezier : BezierCurve_vec) {
    VBOSingleBezierCurve(Bezier);
  }

  // Generate VBO for control points of Bezier Curve
  for (auto& Bezier : BezierCurve_vec) {
    VBOSingleBezierControlPoint(Bezier);
  }

  // Generate VBO for B-spline Curve
  for (auto& BSpline : BSplineCurve_vec) {
    VBOSingleBSplineCurve(BSpline);
  }

  // Generate VBO for control points for B-spline Curve
  for (auto& BSpline : BSplineCurve_vec) {
    VBOSingleBSplineControlPoint(BSpline);
  }
}
void
VBOSingleBSplineCurve(BSplineCurve& BSpline)
{
  GLfloat lines[BSpline.C.size() * 3];
  for (int i = 0, j = 0; i < BSpline.C.size() * 3; i += 3, ++j) {
    lines[i] = BSpline.C.at(j).x;
    lines[i + 1] = BSpline.C.at(j).y;
    lines[i + 2] = 0.0f;
  }
  BSpline.g_vertex_buffer_lines.resize(BSpline.C.size() * 3);
  for (int i = 0; i < BSpline.C.size() * 3; ++i) {
    BSpline.g_vertex_buffer_lines.at(i) = lines[i];
  }

  glGenBuffers(1, &BSpline.vertex_buffer_id_lines);
  glBindBuffer(GL_ARRAY_BUFFER, BSpline.vertex_buffer_id_lines);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BSpline.g_vertex_buffer_lines.size() * 3, lines, GL_DYNAMIC_DRAW);
}
void
VBOSingleBSplineControlPoint(BSplineCurve& BSpline)
{
  GLfloat lines[BSpline.D.size() * 3];
  for (int i = 0, j = 0; i < BSpline.D.size() * 3; i += 3, ++j) {
    lines[i] = BSpline.D.at(j).x;
    lines[i + 1] = BSpline.D.at(j).y;
    lines[i + 2] = 0.0f;
  }
  BSpline.b_vertex_buffer_lines.resize(BSpline.D.size() * 3);
  for (int i = 0; i < BSpline.D.size() * 3; ++i) {
    BSpline.b_vertex_buffer_lines.at(i) = lines[i];
  }

  glGenBuffers(1, &BSpline.b_vertex_buffer_id_lines);
  glBindBuffer(GL_ARRAY_BUFFER, BSpline.b_vertex_buffer_id_lines);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BSpline.b_vertex_buffer_lines.size() * 3, lines, GL_DYNAMIC_DRAW);
}

void
VBOSingleBezierControlPoint(BezierCurve& Bezier)
{
  GLfloat lines[Bezier.B.size() * 3];
  for (int i = 0, j = 0; i < Bezier.B.size() * 3; i += 3, ++j) {
    lines[i] = Bezier.B.at(j).x;
    lines[i + 1] = Bezier.B.at(j).y;
    lines[i + 2] = 0.0f;
  }
  Bezier.b_vertex_buffer_lines.resize(Bezier.B.size() * 3);
  for (int i = 0; i < Bezier.B.size() * 3; ++i) {
    Bezier.b_vertex_buffer_lines.at(i) = lines[i];
  }

  glGenBuffers(1, &Bezier.b_vertex_buffer_id_lines);
  glBindBuffer(GL_ARRAY_BUFFER, Bezier.b_vertex_buffer_id_lines);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Bezier.b_vertex_buffer_lines.size() * 3, lines, GL_DYNAMIC_DRAW);
}

void
VBOSingleBezierCurve(BezierCurve& Bezier)
{
  GLfloat lines[Bezier.C.size() * 3];
  for (int i = 0, j = 0; i < Bezier.C.size() * 3; i += 3, ++j) {
    lines[i] = Bezier.C.at(j).x;
    lines[i + 1] = Bezier.C.at(j).y;
    lines[i + 2] = 0.0f;
  }
  Bezier.g_vertex_buffer_lines.resize(Bezier.C.size() * 3);
  for (int i = 0; i < Bezier.C.size() * 3; ++i) {
    Bezier.g_vertex_buffer_lines.at(i) = lines[i];
  }

  glGenBuffers(1, &Bezier.vertex_buffer_id_lines);
  glBindBuffer(GL_ARRAY_BUFFER, Bezier.vertex_buffer_id_lines);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Bezier.g_vertex_buffer_lines.size() * 3, lines, GL_DYNAMIC_DRAW);
}

void
GenerateBezierCurve()
{
  for (auto& BezierCurve : BezierCurve_vec) {
    BezierCurve.C.clear();
    for (auto& t : BezierCurve.domain) {
      // Case 0: single point when n = 0
      if (BezierCurve.B.size() == 1) {
        break;
      }

      // Case 1: Straight line when n = 1
      if (BezierCurve.B.size() == 2) {
        for (auto& item : BezierCurve.B)
          BezierCurve.C.push_back(item);
        break;
      }

      // End points are always included
      if (t == 0) {
        BezierCurve.C.push_back(BezierCurve.B.at(0));
        continue;
      }

      // End points are always included
      if (t == 1) {
        BezierCurve.C.push_back(BezierCurve.B.at(BezierCurve.B.size() - 1));
        continue;
      }

      DeCasteljau_algorithm(BezierCurve, t);
    }
  }
}

void
GenerateBSplineCurve()
{
  for (auto& BSplineCurve : BSplineCurve_vec) {
    BSplineCurve.C.clear();
    for (auto& t : BSplineCurve.domain) {
      // Case 0: single point when n = 0
      if (BSplineCurve.k == 1) {
        break;
      }

      // Case 1: Straight line when n = 1
      if (BSplineCurve.k == 2) {
        for (auto& item : BSplineCurve.D)
          BSplineCurve.C.push_back(item);
        break;
      }

      // End points are not included according to lecture slide
      if (t == BSplineCurve.domain.at(0)) {
        continue;
      }

      // End points are not included according to lecture slide
      if (t == BSplineCurve.domain.at(BSplineCurve.domain.size() - 1)) {
        continue;
      }

      DeBoor_algorithm(BSplineCurve, t);
    }
  }
}

void
DeCasteljau_algorithm(BezierCurve& B, float t)
{
  // Input: B.B is a vector of points of {b0, b1, b2, ..., bn}
  // Output: C(t) is a point at t, but we add it to B.C

  // Initialize matrix for storage
  std::vector<std::vector<Point>> q;
  q.resize(B.B.size());

  for (int kI = 0; kI < B.B.size(); ++kI) {
    q.at(kI).resize(B.B.size());
    q.at(kI).at(0) = B.B.at(kI);
  }

  // Start iteration
  for (int j = 1; j <= B.n; ++j) {
    for (int i = 0; i <= B.n - j; ++i) {
      q[i][j].x = (1 - t) * q[i][j - 1].x + t * q[i + 1][j - 1].x;
      q[i][j].y = (1 - t) * q[i][j - 1].y + t * q[i + 1][j - 1].y;
    }
  }
  B.C.push_back(q[0][B.n]);
}

void
DeBoor_algorithm(BSplineCurve& B, float u_bar)
{
  // Input:
  // B.D: a vector of control points {b0, b1, b2, ..., bn}
  // k : order
  // u_bar: a single float
  // B.U: a vector of knots {u0, u1, u2, ..., u_{n+k}}

  // Output: C(u_bar) is a 2D point at u_bar, we append it to B.C
  // B.C is where the points defining a B-spline curve

  // Initialize matrix for storage
  std::vector<std::vector<Point>> q;
  q.resize(B.D.size());

  // Initialize a matrix to store the temporary values
  for (int kI = 0; kI < B.D.size(); ++kI) {
    q.at(kI).resize(B.D.size());
    q.at(kI).at(0) = B.D.at(kI);
  }

  // Find I
  auto I = 0;
  for (int kI = B.k - 1; kI < B.U.size(); ++kI) {
    if (kI == B.U.size() - 1)
      break;

    if (B.U.at(kI) <= u_bar && B.U.at(kI + 1) >= u_bar) {
      I = kI;
      break;
    }
  }

  // Start iteration
  for (int j = 1; j <= B.k - 1; ++j) {
    for (int i = I - (B.k - 1); i <= I - j; ++i) {
      q[i][j].x = (B.U.at(i + B.k) - u_bar) * q[i][j - 1].x / (B.U.at(i + B.k) - B.U.at(i + j)) +
        (u_bar - B.U.at(i + j)) * q[i + 1][j - 1].x / (B.U.at(i + B.k) - B.U.at(i + j));
      q[i][j].y = (B.U.at(i + B.k) - u_bar) * q[i][j - 1].y / (B.U.at(i + B.k) - B.U.at(i + j)) +
        (u_bar - B.U.at(i + j)) * q[i + 1][j - 1].y / (B.U.at(i + B.k) - B.U.at(i + j));
    }
  }
  B.C.push_back(q[I - (B.k - 1)][B.k - 1]);
}
