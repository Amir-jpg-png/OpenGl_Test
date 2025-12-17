#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/Renderer.hpp"
#include "include/VertexBuffer.hpp"
#include "include/IndexBuffer.hpp"
#include "include/VertexArray.hpp"
#include "include/Shader.hpp"
// #include "include/Texture.hpp"
#include <string>


int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
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

  window = glfwCreateWindow(900, 900, "OpenGL Shapes Window", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  float positions[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f
  };

  unsigned int indices[] = {
    0, 1, 2, 2, 3, 0
  };

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  VertexArray va;

  VertexBuffer vb(positions, 4 * 4 * sizeof(float));
  VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);
  va.add_buffer(vb, layout);

  const IndexBuffer ib(indices, 6);

  auto shader = Shader("../ressources/shaders/basic.vert");
  shader.bind();

  float b = 0.3f;
  float rate_of_change = 0.01f;

  shader.set_uniform_4f("u_Color", 0.2f, 0.7f, b, 0.5f);

  vb.unbind();
  ib.unbind();
  va.unbind();
  shader.unbind();

  const Renderer renderer;

  while (!glfwWindowShouldClose(window)) {
    shader.bind();
    va.bind();
    ib.bind();
    b += rate_of_change;
    if (b >= 1.0f){
      rate_of_change *= -1;
    }
    else if (b <= 0.0f){
      rate_of_change *= -1;
    }
    shader.set_uniform_4f("u_Color", 0.2f, 0.7f, b, 0.5f);
    renderer.clear();
    renderer.draw(va, ib, shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
