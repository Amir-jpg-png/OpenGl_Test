#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include "GL/glew.h"
#include "Renderer.hpp"

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  GLuint normalized;
  static unsigned int get_size_of_type(unsigned int type)
  {
    switch (type)
    {
    case GL_FLOAT:
      return sizeof(GLfloat);
    case GL_UNSIGNED_INT:
      return sizeof(GLuint);
    case GL_UNSIGNED_BYTE:
      return sizeof(GLubyte);
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout
{
  std::vector<VertexBufferElement> m_elements;
  unsigned int m_stride = 0;

public:
  template <typename T>
  void push(unsigned int count)
  {
  }

  template <>
  void push<float>(unsigned int count)
  {
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += VertexBufferElement::get_size_of_type(GL_FLOAT) * count;
  }

  template <>
  void push<unsigned int>(unsigned int count)
  {
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT) * count;
  }

  template <>
  void push<unsigned char>(unsigned int count)
  {
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE) * count;
  }

  inline const std::vector<VertexBufferElement> &get_elements() const { return m_elements; }
  inline const unsigned int get_stride() const { return m_stride; }
};

#endif // VERTEX_BUFFER_LAYOUT_H
