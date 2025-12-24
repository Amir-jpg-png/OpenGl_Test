#include "../test.h"

namespace test
{

    class TestClearColor : public Test
    {
    private:
        float m_clear_color[4];

    public:
        TestClearColor();
        ~TestClearColor();

        void on_update(float deltaTime) override;
        void on_render() override;
        void on_imgui_render() override;
    };

}