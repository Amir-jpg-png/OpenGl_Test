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
      -50.0f, -50.0f, 0.0f, 0.0f,
      50.0f, -50.0f, 1.0f, 0.0f,
      50.0f, 50.0f, 1.0f, 1.0f,
      -50.0f, 50.0f, 0.0f, 1.0f};

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
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  auto shader = Shader("../ressources/shaders/basic.vert");
  shader.bind();

  shader.set_uniform_1i("u_Texture", 0);

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
  glm::vec3 translationA(200, 200, 0);
  glm::vec3 translationB(100, 200, 0);

  while (!glfwWindowShouldClose(window))
  {
    renderer.clear();

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
    glm::mat4 mvp = proj * view * model;
    shader.bind();
    shader.set_uniform_mat_4f("u_MVP", mvp);

    renderer.draw(va, ib, shader);

    model = glm::translate(glm::mat4(1.0f), translationB);
    mvp = proj * view * model;

    shader.set_uniform_mat_4f("u_MVP", mvp);

    renderer.draw(va, ib, shader);

    {
      ImGui::Begin("Transformations");
      ImGui::SliderFloat3("Tranlation", &translationA.x, 0.0f, 960.0f);
      ImGui::SliderFloat3("Tranlation B", &translationB.x, 0.0f, 960.0f);
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
