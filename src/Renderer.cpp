#include "../include/Renderer.hpp"
#include <iostream>
#include <thread>
#include <alloca.h>
#include "../include/VertexArray.hpp"
#include "../include/IndexBuffer.hpp"
#include "../include/Shader.hpp"

void GL_clear_error() {
  while (glGetError()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

const char *GLErrorToString(const GLenum error) {
  switch (error) {
    case GL_NO_ERROR:
      return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";

    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";

    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";

    case GL_STACK_UNDERFLOW:
      return "GL_STACK_UNDERFLOW";

    case GL_STACK_OVERFLOW:
      return "GL_STACK_OVERFLOW";

    default:
      return "UNKNOWN_GL_ERROR";
  }
}

bool GL_log_call(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] " << GLErrorToString(error) << " " << function <<
        " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

char *get_compile_error(const unsigned int shader_id, GLenum shader_type) {
  int result;
  GLCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    int length;
    GLCall(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
    char *message = static_cast<char *>(alloca(length * sizeof(char)));
    GLCall(glGetShaderInfoLog(shader_id, length, &length, message));
    std::cout << "Failed to compile " << (shader_type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader!" <<
        std::endl;
    std::cout << message << std::endl;
    return message;
  }
  return nullptr;
}


void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
  shader.bind();
  va.bind();
  ib.bind();
  GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
