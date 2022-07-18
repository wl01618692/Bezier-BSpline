//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

#include "comm.hpp"
GLFWwindow* window;


bool show_shadow = false;
bool dynamic_bias = false;

int
main(void)
{
  init();

  // Get the acual framebuffer size:
  int windowWidth, windowHeight;
  glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

  GLuint vao_id;
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  // Create and compile our GLSL program from the shaders
  Pipeline program_depth(depth_rtt_vs, depth_rtt_vs_size, depth_rtt_fs, depth_rtt_fs_size);
  // Create and compile our GLSL program from the shaders
  Pipeline program_shadow_mapping(shadow_mapping_vs, shadow_mapping_vs_size, shadow_mapping_fs, shadow_mapping_fs_size);
  // Create and compile our GLSL program from the shaders
  Pipeline program_quad(passthrough_vs, passthrough_vs_size, simple_texture_fs, simple_texture_fs_size);

  // Load the texture
  GLuint texture = load_texture_from_file("d13_uvmap.jpg");

  // Read our .obj file
  auto object = ReadAsArrayObjects("room_thickwalls.obj");
  object.Create();

  // ---------------------------------------------
  // Render to Texture - specific code begins here
  // ---------------------------------------------
  FrameBufferObject framebuffer;
  framebuffer.Generate();
  framebuffer.Resize(1024, 1024, FBO::NO_COLOR | FBO::DEPTH_TEXTURE | FBO::LINEAR | FBO::COMPARE);

  // The quad's FBO. Used only for visualizing the shadowmap.
  static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
  };
  GLuint quad_vbo_id;
  glGenBuffers(1, &quad_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, quad_vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

  do {

    // Compute the MVP matrix from the light's point of view
    glm::mat4 depth_MVP;
    glm::mat4 depth_model_matrix = glm::mat4(1.0);
    glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);
    if (!spot_light) {
      glm::mat4 depth_projection_matrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
      glm::mat4 depth_view_matrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
      depth_MVP = depth_projection_matrix * depth_view_matrix * depth_model_matrix;
    }
    // or, for spot light
    else {
      glm::vec3 lightPos(5, 20, 20);
      glm::mat4 depth_projection_matrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
      glm::mat4 depth_view_matrix = glm::lookAt(lightPos, lightPos - lightInvDir, glm::vec3(0, 1, 0));
      depth_MVP = depth_projection_matrix * depth_view_matrix * depth_model_matrix;
    }

    // Compute the MVP matrix from keyboard and mouse input
    glm::mat4 P = glm::perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 V = camera.transform();
    glm::mat4 M = glm::mat4(1.0);
    glm::mat4 MVP = P * V * M;

    glm::mat4 bias_matrix(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);
    glm::mat4 depth_bias_MVP = bias_matrix * depth_MVP;

    // Render to our framebuffer
    framebuffer.BindFramebuffer();
    {
      // Render on the whole framebuffer, complete from the lower left corner to the upper right
      glViewport(0, 0, 1024, 1024);
      // We don't use bias in the shader, but instead we draw back faces,
      // which are already separated from the front faces by a small distance
      // (if your geometry is made this way)
      glEnable(GL_CULL_FACE);
      // Cull back-facing triangles -> draw only front-facing triangles
      glCullFace(GL_BACK);
      // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Use our shader
      program_depth.Enable();
      program_depth.SetUniform("depth_MVP", depth_MVP); // Send our transformation to the "MVP" uniform

      // 1rst attribute buffer : vertices
      glEnableVertexAttribArray(0);
      for (auto& m : object.meshes) {
        glBindBuffer(GL_ARRAY_BUFFER, m.vbo_vertex);
        glVertexAttribPointer(0, // The attribute we want to configure
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              0, // stride
                              (void*)0 // array buffer offset
        );
        glDrawArrays(GL_TRIANGLES, 0, m.size_triangles * 3);
      }
      glDisableVertexAttribArray(0);
    }

    // Render to the screen
    framebuffer.UnbindFramebuffer();
    {
      // Render on the whole framebuffer, complete from the lower left corner to the upper right
      glViewport(0, 0, windowWidth, windowHeight);
      glEnable(GL_CULL_FACE);
      // Cull back-facing triangles -> draw only front-facing triangles
      glCullFace(GL_BACK);
      // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Use our shader
      program_shadow_mapping.Enable();
      program_shadow_mapping.SetUniform("MVP", MVP); // Send our transformation to the "MVP" uniform
      program_shadow_mapping.SetUniform("M", M);
      program_shadow_mapping.SetUniform("V", V);
      program_shadow_mapping.SetUniform("depth_bias_MVP", depth_bias_MVP);
      program_shadow_mapping.SetUniform("light_inv_direction_worldspace", lightInvDir);
      program_shadow_mapping.BindTexture("color_map", texture);
      program_shadow_mapping.BindTexture("shadow_map", framebuffer.GetDepthTexture());
      program_shadow_mapping.SetUniform("spot_light", spot_light ? 1 : 0);
      program_shadow_mapping.SetUniform("dynamic_bias", dynamic_bias ? 1 : 0);

      glEnableVertexAttribArray(0); // 1rst attribute buffer : vertices
      glEnableVertexAttribArray(1); // 2nd attribute buffer : UVs
      glEnableVertexAttribArray(2); // 3rd attribute buffer : normals

      for (auto& m : object.meshes) {

        glBindBuffer(GL_ARRAY_BUFFER, m.vbo_vertex);
        glVertexAttribPointer(0, // attribute
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              0, // stride
                              (void*)0 // array buffer offset
        );

        glBindBuffer(GL_ARRAY_BUFFER, m.vbo_texcoord);
        glVertexAttribPointer(1, // attribute
                              2, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              0, // stride
                              (void*)0 // array buffer offset
        );

        glBindBuffer(GL_ARRAY_BUFFER, m.vbo_normal);
        glVertexAttribPointer(2, // attribute
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              0, // stride
                              (void*)0 // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, m.size_triangles * 3);
      }

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
    }

    // Optionally render the shadowmap (for debug only)
    if (show_shadow) {
      // Render only on a corner of the window (or we we won't see the real rendering...)
      glViewport(0, 0, 512, 512);

      // Use our shader
      program_quad.Enable();
      program_quad.BindTexture("tex", framebuffer.GetDepthTexture());

      // 1rst attribute buffer : vertices
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, quad_vbo_id);
      glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
                            3, // size
                            GL_FLOAT, // type
                            GL_FALSE, // normalized?
                            0, // stride
                            (void*)0 // array buffer offset
      );

      // Draw the triangle
      glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles
      glDisableVertexAttribArray(0);
    }

    // Draw GUI
    if (begin_gui()) {
      ImGui::Checkbox("Rotate Light", &rotate_light);
      ImGui::Checkbox("Spot Light", &spot_light);
      ImGui::Checkbox("Show Shadow", &show_shadow);
      ImGui::Checkbox("Dynamic Bias", &dynamic_bias);
      end_gui();
    }

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  // Cleanup VBO and shader
  object.Clear();
  program_depth.Clear();
  program_shadow_mapping.Clear();
  program_quad.Clear();
  framebuffer.Clear();
  glDeleteTextures(1, &texture);
  glDeleteBuffers(1, &quad_vbo_id);
  glDeleteVertexArrays(1, &vao_id);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
