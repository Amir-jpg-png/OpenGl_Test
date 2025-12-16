#include "../include/VertexArray.hpp"
#include "../include/Renderer.hpp"

VertexArray::VertexArray(){
  GLCall(glGenVertexArrays(1, &m_render_id));
  GLCall(glBindVertexArray(m_render_id));
}

VertexArray::~VertexArray(){
  GLCall(glDeleteVertexArrays(1, &m_render_id));
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
  bind();
  vb.bind();
  const auto& elements = layout.get_elements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++){
    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*) offset));
    offset += element.count * VertexBufferElement::get_size_of_type(element.type);
  }

}

void VertexArray::bind() const{
  GLCall(glBindVertexArray(m_render_id));
}

void VertexArray::unbind() const{
  GLCall(glBindVertexArray(0));
}
