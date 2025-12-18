#ifndef OPENGLTEST_SHADER_H
#define OPENGLTEST_SHADER_H
#include <string>
#include <unordered_map>
#include "../lib/glm/glm.hpp"

class Shader {
        std::string m_filepath;
        unsigned int m_renderer_id = 0;
        std::unordered_map<std::string, int> m_uniforms_cache;

public:
        explicit Shader(const std::string &filepath);

        ~Shader();

        void bind() const;

        void unbind() const;

        void set_uniform_4f(const std::string &name, float v0, float v1, float v2, float v3);

        void set_uniform_1i(const std::string &name, int value);

        void set_uniform_mat_4f(const std::string &name, const glm::mat4 &matrix);

private:
        void parse_shader(std::string &vertex_source, std::string &fragment_source) const;

        unsigned int compile_shader(unsigned int type, const std::string &source) const;

        unsigned int create_shader(const std::string &vertex_shader, const std::string &fragment_shader) const;

        int get_and_cache_uniform_location(const std::string &name);
};

#endif //OPENGLTEST_SHADER_H
