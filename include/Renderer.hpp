#ifndef RENDERER_H
#define RENDERER_H

class VertexArray;
class IndexBuffer;
class Shader;
#include <GL/glew.h>   // or <glad/glad.h>
#include <string>


#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GL_clear_error();\
x;\
ASSERT(GL_log_call(#x, __FILE__, __LINE__))

#include <GL/glew.h>
#include <signal.h>
#include <string>

class Renderer {
public:
  void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

  void clear() const;
};


void GL_clear_error();

bool GL_log_call(const char *function, const char *file, int line);

char *get_compile_error(const unsigned int shader_id, GLenum shader_type);


#endif //RENDERER_H
