#include "test.h"

namespace test
{
    TestMenu::TestMenu(Test *&currentTestPointer)
        : m_CurrentTest(currentTestPointer)
    {
    }

    void TestMenu::on_imgui_render()
    {
        for (auto &test : m_Tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                m_CurrentTest = test.second();
            }
        }
    }

    TestMenu::~TestMenu()
    {
    }
}