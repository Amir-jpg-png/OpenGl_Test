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
  glm::vec4 pos(100.0f, 100.0f, 0.0f, 1.0f);
  glm::vec4 res = proj * pos;
  auto shader = Shader("../ressources/shaders/basic.vert");
  shader.bind();

  shader.set_uniform_1i("u_Texture", 0);
  shader.set_uniform_mat_4f("u_MVP", proj);

  const Texture texture("../ressources/textures/TechSupportLogo.png");
  texture.bind();

  vb.unbind();
  ib.unbind();
  va.unbind();
  shader.unbind();

  const Renderer renderer;

  while (!glfwWindowShouldClose(window))
  {
    shader.bind();
    renderer.clear();
    renderer.draw(va, ib, shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
