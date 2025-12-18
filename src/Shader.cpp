#include "../include/Shader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include "../lib/glm/gtc/type_ptr.hpp"
#include "../include/Renderer.hpp"

Shader::Shader(const std::string &filepath)
    : m_filepath(filepath)
{
    std::string vertex_source;
    std::string fragment_source;
    parse_shader(vertex_source, fragment_source);
    m_renderer_id = create_shader(vertex_source, fragment_source);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_renderer_id));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_renderer_id));
}

void Shader::unbind() const
{
    if (m_renderer_id != 0)
    {
        GLCall(glUseProgram(0));
    }
}

void Shader::set_uniform_4f(const std::string &name, const float v0, const float v1, const float v2,
                            const float v3)
{
    GLCall(glUniform4f(get_and_cache_uniform_location(name), v0, v1, v2, v3));
}

int Shader::get_and_cache_uniform_location(const std::string &name)
{
    if (m_uniforms_cache.find(name) != m_uniforms_cache.end())
    {
        return m_uniforms_cache.at(name);
    }
    GLCall(const int location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if (location == -1)
    {
        std::cout << "WARNING: Uniform " + name + " does not exist!" << std::endl;
    }
    else
    {
        m_uniforms_cache[name] = location;
    }
    return location;
}

unsigned int Shader::compile_shader(const unsigned int type, const std::string &source) const
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    if (get_compile_error(id, type) != nullptr)
    {
        exit(-1);
    }
    return id;
}

void Shader::parse_shader(std::string &vertex_source, std::string &fragment_source) const
{
    enum shader_type
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::ifstream stream(m_filepath);
    if (!stream.is_open())
    {
        std::cerr << "ERROR: Could not open shader file: " << m_filepath << "\n";
        exit(-1);
    }
    std::string line;
    std::stringstream ss[2];
    shader_type mode = NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                mode = VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                mode = FRAGMENT;
            }
        }
        else if (mode != NONE)
        {
            ss[mode] << line << "\n";
        }
        else
        {
            std::cerr << "No line #shader. Neither vertex nor fragment shader" << std::endl;
            exit(-1);
        }
    }
    vertex_source = ss[VERTEX].str();
    fragment_source = ss[FRAGMENT].str();
}

unsigned int Shader::create_shader(const std::string &vertex_shader, const std::string &fragment_shader) const
{
    const unsigned int program = glCreateProgram();
    const unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    const unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glDetachShader(program, vs));
    GLCall(glDetachShader(program, fs));
    GLCall(glValidateProgram(program));
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return program;
}

void Shader::set_uniform_1i(const std::string &name, int value)
{
    GLCall(glUniform1i(get_and_cache_uniform_location(name), value));
}

void Shader::set_uniform_mat_4f(const std::string &name, const glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(get_and_cache_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}