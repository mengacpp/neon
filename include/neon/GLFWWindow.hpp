#pragma once

#include "window.hpp"

#include "GLFW/glfw3.h"

namespace neon
{

class GLFWWindow : public Window
{
public:
    GLFWWindow(const std::string &name);
    ~GLFWWindow();

    void init() override;

    void swap_buffers() override {glfwSwapBuffers(m_glfwwindow_handle); }
    void poll_events() override {glfwPollEvents(); }
    bool should_close() override {return glfwWindowShouldClose(m_glfwwindow_handle); }

private:
    GLFWwindow *m_glfwwindow_handle;

};

}
