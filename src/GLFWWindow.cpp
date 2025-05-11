#include "GLFW/glfw3.h"

#include "neon/GLFWWindow.hpp"

#include "oxygen/errors.hpp"
#include "oxygen/log.hpp"

using namespace oxygen;

static bool is_glfw_init = false;
static int active_glfw_windows = 0;

neon::GLFWWindow::GLFWWindow(const std::string &name)
: Window(name)
{
    if(!is_glfw_init)
    {
        if(!glfwInit())
        {
            throw FatalException(LogError() << "GLFW initialization failed.");
        }
    
        is_glfw_init = true;
    }

    active_glfw_windows++;
}

void neon::GLFWWindow::init()
{
    if(m_is_initialized)
    {
        glfwMakeContextCurrent(m_glfwwindow_handle);
        return;
    }

    if(!is_glfw_init)
    {
        throw FatalException(
            LogError() << "Window initialization failed on '" << m_name << "':" <<
            "GLFW not initialized");
    }

    m_glfwwindow_handle  = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!m_glfwwindow_handle)
    {
        glfwTerminate();
        throw FatalException(
                LogError() << "Window initialization failed on '" << m_name << "'");
        
    }

    m_is_initialized = true;

}

neon::GLFWWindow::~GLFWWindow()
{
    active_glfw_windows--;
    if(active_glfw_windows < 1)
    {
        glfwTerminate();
        is_glfw_init = false;

    }
}

void neon::GLFWWindow::swap_buffers() {glfwSwapBuffers(m_glfwwindow_handle); }
void neon::GLFWWindow::poll_events() {glfwPollEvents(); }
bool neon::GLFWWindow::should_close() {return glfwWindowShouldClose(m_glfwwindow_handle); }