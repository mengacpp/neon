#pragma once

#include "window.hpp"

#include "oxygen/outcome.hpp"

class GLFWwindow;

namespace neon
{

class GLFWWindow : public Window
{
public:
    GLFWWindow(const std::string &name);
    ~GLFWWindow();

    xgn::Outcome init() override;

    xgn::Outcome swap_buffers() override;
    xgn::Outcome poll_events() override;
    bool should_close() override;

private:
    GLFWwindow *m_glfwwindow_handle;

};

}
