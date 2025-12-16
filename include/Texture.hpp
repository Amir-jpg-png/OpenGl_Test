#ifndef OPENGLTEST_TEXTURE_H
#define OPENGLTEST_TEXTURE_H
#include "Renderer.hpp"

class Texture {
    unsigned int m_renderer_id;
    std::string m_filepath;
    unsigned char *m_buffer;
    //bpp -> bits per pixel
    int m_width, m_height, m_bpp;

public:
    Texture(const std::string &filepath);

    ~Texture();

    void bind(unsigned int slot = 0) const;

    void unbind() const;

    inline int get_width() const { return m_width; }
    inline int get_height() const { return m_height; }
};

#endif //OPENGLTEST_TEXTURE_H
