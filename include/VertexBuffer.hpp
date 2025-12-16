#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer{
  unsigned int m_renderer_id;
  public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};

#endif // VERTEX_BUFFER_H
