#include "neon/window.hpp"

#include "neon/GLFWWindow.hpp"

#include <iostream>

neon::Window::Window(const std::string &name)
{
    
}

std::unique_ptr<neon::Window> neon::create_window(const std::string &name)
{
    try {
    auto window = std::make_unique<GLFWWindow>(name);
    return window;
    } catch (const std::exception &e) {
        std::cout << e.what();
        exit(-1);
    }

    return nullptr;
}
