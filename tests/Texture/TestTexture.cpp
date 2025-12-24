#include "TestTexture.h"
#include <iostream>

namespace test
{
    TestTexture::TestTexture()
        : m_translationA(200, 200, 0),
          m_translationB(400, 200, 0)
    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f};

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0};

        m_shader = std::make_unique<Shader>("../ressources/shaders/basic.vert");
        m_vao = std::make_unique<VertexArray>();
        m_ibo = std::make_unique<IndexBuffer>(indices, 6);
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_vao->add_buffer(*m_vbo, layout);

        m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        m_shader->bind();

        m_shader->set_uniform_1i("u_Texture", 0);

        m_texture = std::make_unique<Texture>("../ressources/textures/TechSupportLogo.png");

        m_texture->bind();
    }
    void TestTexture::on_render()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        m_texture->bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->set_uniform_mat_4f("u_MVP", mvp);
        m_renderer.draw(*m_vao, *m_ibo, *m_shader);
        model = glm::translate(glm::mat4(1.0f), m_translationB);
        mvp = m_proj * m_view * model;
        m_shader->set_uniform_mat_4f("u_MVP", mvp);
        m_renderer.draw(*m_vao, *m_ibo, *m_shader);
    }

    void TestTexture::on_imgui_render()
    {
        ImGui::SliderFloat3("Tranlation", &m_translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Tranlation B", &m_translationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO);
    }

    void TestTexture::on_update(float deltaTime)
    {

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->bind();
        m_shader->set_uniform_mat_4f("u_MVP", mvp);

        m_renderer.draw(*m_vao, *m_ibo, *m_shader);

        model = glm::translate(glm::mat4(1.0f), m_translationB);
        mvp = m_proj * m_view * model;

        m_shader->set_uniform_mat_4f("u_MVP", mvp);

        m_renderer.draw(*m_vao, *m_ibo, *m_shader);
    }

    TestTexture::~TestTexture()
    {
        GLCall(glDisable(GL_BLEND));
    }

}