#pragma once
#ifdef _WIN32

#define UNICODE
#define _UNICODE

#include  <windows.h>
#include <string> //TODO remove this

#include "window.hpp"

namespace neon
{

class WindowsWindow : public Window
{
public:
    WindowsWindow(const std::string &name);

    void init() override;

    void open() override;

private:

    HINSTANCE m_hinstance;
    HWND m_hwindow;
};

}

#endif