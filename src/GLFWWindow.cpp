#include "GLFW/glfw3.h"

#include "neon/GLFWWindow.hpp"

using namespace xgn;

static bool is_glfw_init = false;
static int active_glfw_windows = 0;

neon::GLFWWindow::GLFWWindow(const std::string &name) : Window(name) {}

Outcome neon::GLFWWindow::init() {
  if (!is_glfw_init) {
    if (!glfwInit()) {
      return Outcome(
        OutcomeCode::Unknown, 
        "GLFW Initialization failed.");
    }

    is_glfw_init = true;
  }
  active_glfw_windows++;

  if (m_is_initialized) {
    glfwMakeContextCurrent(m_glfwwindow_handle);
    return outcome_ok();
  }

  m_glfwwindow_handle = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!m_glfwwindow_handle) {
    glfwTerminate();
    return Outcome(
      OutcomeCode::Unknown,
      "GLFW Window initialization failed on '" + m_name + "'.");
  }

  m_is_initialized = true;
  return outcome_ok();
}

neon::GLFWWindow::~GLFWWindow() {
  active_glfw_windows--;
  if (active_glfw_windows < 1) {
    glfwTerminate();
    is_glfw_init = false;
  }
}

Outcome neon::GLFWWindow::swap_buffers() { 
  glfwSwapBuffers(m_glfwwindow_handle); 
  return outcome_ok();
}
Outcome neon::GLFWWindow::poll_events() { 
  glfwPollEvents(); 
  return outcome_ok();
}

bool neon::GLFWWindow::should_close() {
  return glfwWindowShouldClose(m_glfwwindow_handle);
}