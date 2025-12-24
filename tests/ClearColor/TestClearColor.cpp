#include "TestClearColor.h"
#include <iostream>

namespace test
{
    TestClearColor::TestClearColor() : m_clear_color{0.7, 1.0, 0.0, 1.0} {}
    void TestClearColor::on_render()
    {
        GLCall(glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::on_imgui_render()
    {
        ImGui::ColorEdit4("Clear Color", m_clear_color);
    }

    void TestClearColor::on_update(float deltaTime)
    {
        const auto &renderer = Renderer::get();
        glm::vec4 clear_colors(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
        renderer.set_clear_color(clear_colors);
    }

    TestClearColor::~TestClearColor() = default;

}