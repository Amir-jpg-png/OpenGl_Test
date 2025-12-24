#ifndef RENDERER_H
#define RENDERER_H

class VertexArray;
class IndexBuffer;
class Shader;
#include <GL/glew.h> // or <glad/glad.h>
#include <string>

#define ASSERT(x) \
  if (!(x))       \
    raise(SIGTRAP);
#define GLCall(x)   \
  GL_clear_error(); \
  x;                \
  ASSERT(GL_log_call(#x, __FILE__, __LINE__))

#include <GL/glew.h>
#include <signal.h>
#include <string>
#include "../lib/glm/glm.hpp"

class Renderer
{
  Renderer() {}

public:
  void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

  void clear() const;
  void set_clear_color(const glm::vec4 &clear_colors) const;
  static inline Renderer &get()
  {
    static Renderer renderer;
    return renderer;
  }
  Renderer(Renderer &&other) = delete;
  Renderer(Renderer &) = delete;
  Renderer operator=(Renderer &&) = delete;
  Renderer operator=(Renderer) = delete;
  Renderer operator=(Renderer &) = delete;
};

void GL_clear_error();

bool GL_log_call(const char *function, const char *file, int line);

char *get_compile_error(const unsigned int shader_id, GLenum shader_type);

#endif // RENDERER_H
