#include "../include/IndexBuffer.hpp"
#include "../include/Renderer.hpp"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count) {
  ASSERT(sizeof(unsigned int) == sizeof(GLuint));
  GLCall(glGenBuffers(1, &m_renderer_id));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer() {
  GLCall(glDeleteBuffers(1, &m_renderer_id));
}
