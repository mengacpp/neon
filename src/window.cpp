#include "neon/window.hpp"

#ifdef _WIN32
#include "neon/windows-window.hpp"
#endif

neon::Window::Window(const std::string &name)
{
    
}

std::unique_ptr<neon::Window> neon::create_window(const std::string &name)
{
#ifdef _WIN32
    return std::make_unique<WindowsWindow>(name);
#endif
    return nullptr;
}
