#ifndef TESTS_H
#define TESTS_H
#include <iostream>
#include <vector>
#include <functional>
#include "../lib/imgui/imgui.h"
#include "../include/Renderer.hpp"

namespace test
{

    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}
        virtual void on_update(float deltaTime) {}
        virtual void on_render() {}
        virtual void on_imgui_render() {}
    };

    class TestMenu : public Test
    {
        std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
        test::Test *&m_CurrentTest;

    public:
        TestMenu(Test *&currentTestPointer);
        ~TestMenu();
        void on_update(float deltaTime) {}
        void on_render() {}
        void on_imgui_render() override;
        template <typename T>
        void register_test(const std::string &name)
        {
            std::cout << "Registering test " << name << std::endl;
            m_Tests.push_back(std::make_pair(name, []
                                             { return new T(); }));
        }
    };

}

#endif // TESTS_H