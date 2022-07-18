//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#pragma once

#include "util.hpp"

#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct TriangleArrayObjects {
  struct Mesh {
    std::unique_ptr<float> vertices;
    std::unique_ptr<float> normals;
    std::unique_ptr<float> texcoords;
    size_t size_triangles;
    GLuint vbo_vertex, vbo_normal, vbo_texcoord;
  };
  std::vector<Mesh> meshes;

  std::string name;
  glm::vec3 center = glm::vec3(0.f);
  glm::vec3 lower, upper;
  float scale = 1.f;

  void
  Clear();

  void
  Create();

  glm::mat4
  GetModelMatrix();
};

TriangleArrayObjects
ReadAsArrayObjects(const std::string& inputfile);
