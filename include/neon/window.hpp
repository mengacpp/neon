#pragma once

#include <string>
#include <memory>

namespace neon
{

class Window;

std::unique_ptr<Window> create_window(const std::string &name);

class Window
{
public:
    Window(const std::string &name);

    virtual ~Window() = default;

    virtual void init() = 0;

    virtual void open() = 0;

protected:
    std::string m_name;

    bool m_is_initialized;

    bool m_is_running;
private:    


};


}