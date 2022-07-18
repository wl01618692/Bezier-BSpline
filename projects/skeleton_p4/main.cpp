//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

// Include standard headers
#include "gui.h"
#include "helper.h"
#include "shaders.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

GLFWwindow* window;
bool show_menu = false;
std::vector<BSplineCurve> BSplineCurve_vec;
std::vector<BezierCurve> BezierCurve_vec;

static void
KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE); // close window
  }
  else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
    show_menu = !show_menu;
  }
}

int
main(int argc, char** argv)
{
  // Readfile
  Readfile(argc, argv);

  // Initialise GLFW
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  const char* glsl_version = "#version 150"; // GL 3.3 + GLSL 150
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "ECS 175 Demo (Press 'g' for GUI)", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    throw std::runtime_error("Failed to open GLFW window. If you have a GPU that is "
                             "not 3.3 compatible, try a lower OpenGL version.");
  }

  // Callback
  glfwSetKeyCallback(window, KeyCallback);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // Load GLAD symbols
  int err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;
  if (err) {
    throw std::runtime_error("Failed to initialize OpenGL loader!");
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);

  // Create and compile our GLSL program from the shaders
  GLuint program_id =
    load_program_from_embedding((char*)vertexshader, vertexshader_size, (char*)fragmentshader, fragmentshader_size);

  // Get a handle for our "MVP" uniform
  GLuint matrix_id = glGetUniformLocation(program_id, "Matrix");
  glm::mat4 matrix = { 1.086396,  -0.993682, -0.687368, -0.685994, 0.000000, 2.070171, -0.515526, -0.514496,
                       -1.448528, -0.745262, -0.515526, -0.514496, 0.000000, 0.000000, 5.642426,  5.830953 };

  // Control flow in fragment shader
  GLuint original_id = glGetUniformLocation(program_id, "original");
  GLuint bezier_id = glGetUniformLocation(program_id, "bezier");
  bool original;
  bool bezier;

  // VBO
  CreateVBO();

  // ImGui
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Initialize Dear ImGui
    ImGui_ImplGlfw_InitForOpenGL(window, true /* 'true' -> allow imgui to capture keyboard inputs */);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {

    /* TODO you compute your curves here */
    // Bezier Curve (DeCasteljau algorithm)
    GenerateBezierCurve();

    // B-spline Curve (De Boor algorithm)
    GenerateBSplineCurve();

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(program_id);

    // Draw
    for (auto& geometry : BSplineCurve_vec) {
      // Draw B-spline curve in red
      {
        // Control flow in fragment shader
        original = false;
        bezier = false;
        glUniform1i(bezier_id, bezier);
        glUniform1i(original_id, original);
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &matrix[0][0]);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, geometry.vertex_buffer_id_lines);
        glVertexAttribPointer(0,
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              sizeof(float) * 3, // stride
                              (void*)0 // array buffer offset
        );
        glDrawArrays(GL_LINE_STRIP, 0, geometry.C.size());
        glDisableVertexAttribArray(0);
      }
      // Draw control points in white
      {
        // Control flow in fragment shader
        original = true;
        bezier = false;
        glUniform1i(original_id, original);
        glUniform1i(bezier_id, bezier);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, geometry.b_vertex_buffer_id_lines);
        glVertexAttribPointer(0,
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              sizeof(float) * 3, // stride
                              (void*)0 // array buffer offset
        );
        glDrawArrays(GL_LINE_STRIP, 0, geometry.D.size());
        glDisableVertexAttribArray(0);
      }
    }

    for (auto& geometry : BezierCurve_vec) {
      // Draw Bezier Curve in red
      {
        // Control flow in fragment shader
        original = false;
        bezier = true;
        glUniform1i(bezier_id, bezier);
        glUniform1i(original_id, original);
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &matrix[0][0]);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, geometry.vertex_buffer_id_lines);
        glVertexAttribPointer(0,
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              sizeof(float) * 3, // stride
                              (void*)0 // array buffer offset
        );
        glDrawArrays(GL_LINE_STRIP, 0, geometry.C.size());
        glDisableVertexAttribArray(0);
      }
      // Draw control points in green
      {
        // Control flow in fragment shader
        bezier = true;
        original = true;
        glUniform1i(bezier_id, bezier);
        glUniform1i(original_id, original);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, geometry.b_vertex_buffer_id_lines);
        glVertexAttribPointer(0,
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              sizeof(float) * 3, // stride
                              (void*)0 // array buffer offset
        );
        glDrawArrays(GL_LINE_STRIP, 0, geometry.B.size());
        glDisableVertexAttribArray(0);
      }
    }

    // Initialization
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {
      // TODO Draw GUI
      if (show_menu)
        ShowMenu(&show_menu, window);
    }

    // Render GUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup VBO and shader
  for (auto& geometry : BezierCurve_vec)
    glDeleteBuffers(1, &geometry.vertex_buffer_id_lines);

  for (auto& geometry : BSplineCurve_vec)
    glDeleteBuffers(1, &geometry.vertex_buffer_id_lines);

  glDeleteProgram(program_id);
  glDeleteVertexArrays(1, &vertex_array_id);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  // Output file
  Outputfile(argc, argv);

  return 0;
}
