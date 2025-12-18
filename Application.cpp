#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/Renderer.hpp"
#include "include/VertexBuffer.hpp"
#include "include/IndexBuffer.hpp"
#include "include/VertexArray.hpp"
#include "include/Shader.hpp"
#include "include/Texture.hpp"
#include <string>
#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_glfw.h"
#include "lib/imgui/imgui_impl_opengl3.h"

int main()
{
  GLFWwindow *window;

  if (!glfwInit())
  {
    std::cout << "Failed to init GLFW" << std::endl;
    return -1;
  }

#ifndef APPLE
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(960, 540, "OpenGL Shapes Window", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  float positions[] = {
      100.0f, 100.0f, 0.0f, 0.0f,
      200.0f, 100.0f, 1.0f, 0.0f,
      200.0f, 200.0f, 1.0f, 1.0f,
      100.0f, 200.0f, 0.0f, 1.0f};

  unsigned int indices[] = {
      0, 1, 2, 2, 3, 0};

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  VertexArray va;

  VertexBuffer vb(positions, 4 * 4 * sizeof(float));
  VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);
  va.add_buffer(vb, layout);

  const IndexBuffer ib(indices, 6);

  glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
  glm::mat4 mvp = proj * view * model;
  auto shader = Shader("../ressources/shaders/basic.vert");
  shader.bind();

  shader.set_uniform_1i("u_Texture", 0);
  shader.set_uniform_mat_4f("u_MVP", mvp);

  const Texture texture("../ressources/textures/TechSupportLogo.png");
  texture.bind();

  vb.unbind();
  ib.unbind();
  va.unbind();
  shader.unbind();

  const Renderer renderer;

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 150");
  ImGui::StyleColorsDark();

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  while (!glfwWindowShouldClose(window))
  {
    renderer.clear();

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    renderer.draw(va, ib, shader);

    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}
