#include "../test.h"
#include <memory>
#include "../../include/Renderer.hpp"
#include "../../include/VertexBuffer.hpp"
#include "../../include/IndexBuffer.hpp"
#include "../../include/VertexArray.hpp"
#include "../../include/Shader.hpp"
#include "../../include/Texture.hpp"
#include "../../lib/glm/gtc/matrix_transform.hpp"

namespace test
{

    class TestTexture : public Test
    {
    private:
        Renderer &m_renderer = Renderer::get();
        std::unique_ptr<Shader> m_shader;
        glm::vec3 m_translationA, m_translationB;
        glm::mat4 m_proj;
        glm::mat4 m_view;
        std::unique_ptr<VertexArray> m_vao;
        std::unique_ptr<VertexBuffer> m_vbo;
        std::unique_ptr<IndexBuffer> m_ibo;
        std::unique_ptr<Texture> m_texture;

    public:
        TestTexture();
        ~TestTexture();

        void on_update(float deltaTime) override;
        void on_render() override;
        void on_imgui_render() override;
    };

}