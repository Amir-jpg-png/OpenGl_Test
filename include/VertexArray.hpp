#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray{
  unsigned int m_render_id;
  public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
    void bind() const;
    void unbind() const;
};

#endif // VERTEX_ARRAY_H
