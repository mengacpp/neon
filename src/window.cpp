#include "neon/window.hpp"

#include "neon/GLFWWindow.hpp"

neon::Window::Window(const std::string &name)
  : m_name(name)
{
    
}

xgn::OutcomeOr<std::unique_ptr<neon::Window>> neon::create_window(const std::string &name)
{
    // we use exceptions here because its the stdlib way of handling errors
    try {
      std::unique_ptr<Window> window = std::make_unique<GLFWWindow>(name);
      return window;
    } 
    catch (const std::exception &e) {
      return xgn::Outcome(xgn::OutcomeCode::Unknown, e.what());
    }

    return xgn::Outcome(xgn::OutcomeCode::Unknown, "Unreachable code");
}
