#pragma once

#include <iostream>
#include <memory>

namespace neon
{

class Window
{
public:
    Window(const std::string &name);
    virtual ~Window() = default;

    virtual int init() = 0;

    virtual int open() = 0;

protected:
    std::string m_name;

    bool m_is_initialized;

    bool m_is_running;
private:
};

std::unique_ptr<Window> create_window(const std::string &name);

}