#include "neon/window.hpp"

#include "neon/windows-window.hpp"

#include "oxygen/math.hpp"

namespace neon
{

Window::Window(const std::string &name) : m_name(name), m_is_initialized(false)
{
    std::cout << name << " created\n";
}

std::unique_ptr<Window> create_window(const std::string &name)
{
#ifdef _WIN32
    return std::make_unique<WindowsWindow>(name);
#endif
    return nullptr;
}
}