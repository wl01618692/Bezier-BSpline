#include "comm.hpp"

bool imgui = true;

ArcballCamera camera(vec3(14, 6, 4), vec3(0, 1, 0), vec3(0, 1, 0));
ArcballCamera light(vec3(4, 3, -3), vec3(0, 0, 0), vec3(0, 1, 0));
bool rotate_light = false;
bool spot_light = false;

void
update_arcball(ArcballCamera& ball, GLFWwindow* window, double xpos, double ypos)
{
  int left_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  int right_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  static vec2 prev_cursor;
  vec2 cursor((xpos / width - 0.5f) * 2.f, (0.5f - ypos / height) * 2.f);

  // right click -> zoom
  if (right_state == GLFW_PRESS || right_state == GLFW_REPEAT) {
    ball.zoom(cursor.y - prev_cursor.y);
  }

  // left click -> rotate
  if (left_state == GLFW_PRESS || left_state == GLFW_REPEAT) {
    ball.rotate(prev_cursor, cursor);
  }

  prev_cursor = cursor;
}

void
keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (ImGui::GetIO().WantCaptureKeyboard) {
    return;
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    // close window
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
    imgui = !imgui;
  }
}

void
cursor(GLFWwindow* window, double xpos, double ypos)
{
  if (ImGui::GetIO().WantCaptureMouse) {
    return;
  }

  if (!rotate_light)
    update_arcball(camera, window, xpos, ypos);
  else
    update_arcball(light, window, xpos, ypos);
}

bool
begin_gui()
{
  if (!imgui)
    return false;

  // Initialization
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // measure frame rate
  const float fps = get_framerate();

  // draw a fixed GUI window
  const float distance = 10.0f;
  static int corner = 0;
  ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - distance : distance,
                             (corner & 2) ? ImGui::GetIO().DisplaySize.y - distance : distance);
  ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
  ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.3f)); // Transparent background
  const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
  bool ret = ImGui::Begin("Information", NULL, flags);
  if (ret) {
    ImGui::Text("FPS (Hz): %.f\n", fps);
    return true;
  }
  else {
    return false;
  }
}

void
end_gui()
{
  ImGui::End();
  ImGui::PopStyleColor();

  // Render GUI
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void
init()
{
  // Initialise GLFW
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // We would expect width and height to be 1024 and 768
  int windowWidth = 1024;
  int windowHeight = 768;

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(windowWidth, windowHeight, "ECS 175 - Shadows", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    throw std::runtime_error("Failed to open GLFW window. If you have a GPU that is "
                             "not 3.3 compatible, try a lower OpenGL version.");
  }

  glfwMakeContextCurrent(window);

  // Load GLAD symbols
  int err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;
  if (err) {
    throw std::runtime_error("Failed to initialize OpenGL loader!");
  }

  // ImGui
  {
    const char* glsl_version = "#version 150"; // GL 3.3 + GLSL 150

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // or ImGui::StyleColorsClassic();

    // Initialize Dear ImGui
    ImGui_ImplGlfw_InitForOpenGL(window, true /* 'true' -> allow imgui to capture keyboard inputs */);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  glfwSetKeyCallback(window, keyboard);
  glfwSetCursorPosCallback(window, cursor);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set the mouse at the center of the screen
  glfwPollEvents();

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
}

void
finalize()
{
  // Cleanup ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}
