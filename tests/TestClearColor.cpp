#include "TestClearColor.h"
#include "../include/Renderer.hpp"
#include "../lib/imgui/imgui.h"
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
        // No update logic needed for this test
    }

    TestClearColor::~TestClearColor() = default;

}