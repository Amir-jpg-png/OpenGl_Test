#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer {
  unsigned int m_renderer_id;
  unsigned int m_count;

public:
  IndexBuffer(const unsigned int *data, unsigned int count);

  ~IndexBuffer();

  void bind() const;

  void unbind() const;

  inline unsigned int get_count() const {
    return m_count;
  }
};

#endif //INDEX_BUFFER_H
