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
#include "tests/ClearColor/TestClearColor.h"
#include "tests/Texture/TestTexture.h"

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

  window = glfwCreateWindow(960, 540, "OpenGL Test", nullptr, nullptr);
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

  const Renderer &renderer = Renderer::get();

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 150");
  ImGui::StyleColorsDark();

  test::Test *currentTest = nullptr;
  test::TestMenu *menu = new test::TestMenu(currentTest);
  currentTest = menu;
  menu->register_test<test::TestClearColor>("Clear Color");
  menu->register_test<test::TestTexture>("Test Texture");

  while (!glfwWindowShouldClose(window))
  {
    renderer.clear();

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    if (currentTest)
    {
      currentTest->on_update(0.0f);
      currentTest->on_render();
      ImGui::Begin("Test");
      if (currentTest != menu && ImGui::Button("<-"))
      {
        delete currentTest;
        currentTest = menu;
      }
      currentTest->on_imgui_render();
      ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  delete currentTest;
  if (currentTest != menu)
  {
    delete menu;
  }

  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}
