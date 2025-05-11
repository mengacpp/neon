#pragma once

#include "window.hpp"

class GLFWwindow;

namespace neon
{

class GLFWWindow : public Window
{
public:
    GLFWWindow(const std::string &name);
    ~GLFWWindow();

    void init() override;

    void swap_buffers() override;
    void poll_events() override;
    bool should_close() override;

private:
    GLFWwindow *m_glfwwindow_handle;

};

}
