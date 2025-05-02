#pragma once
#ifdef _WIN32

#define UNICODE
#define _UNICODE

#include  <windows.h>
#include <string>

#include "window.hpp"

namespace neon
{

class WindowsWindow : public Window
{
public:
    WindowsWindow(const std::string &name);

    int init() override;

    int open() override;

private:

    // TODO move to oxygen as string_to_wstring()
    std::wstring get_wstring_name();

    HINSTANCE m_hinstance;
    HWND m_hwindow;
};

}

#endif