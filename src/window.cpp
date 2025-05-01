#include "neon/window.hpp"

#include "oxygen/math.hpp"

namespace neon
{
Window::Window(std::string name)
{
    std::cout << name << " " << oxy::math::max(1, 3) << "\n";
}
}