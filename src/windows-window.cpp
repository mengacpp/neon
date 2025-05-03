#ifdef _WIN32

#include "neon/windows-window.hpp"

#include <string>
#include <locale>
#include <codecvt>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

neon::WindowsWindow::WindowsWindow(const std::string &name)
: Window(name)
{

}

int neon::WindowsWindow::init()
{
    m_hinstance = GetModuleHandle(nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = m_hinstance;
    wc.lpszClassName = L"oxygenWindowClass";

    if (!RegisterClass(&wc)) {
        std::cout << "Failed to register window class\n";
        return -1;
    }

    std::cout << "window initialized\n";
    m_is_initialized = true;

    return 0;
}

int neon::WindowsWindow::open()
{
    if(!m_is_initialized)
    {
        std::cout << "Can't open Window " << m_name << ": not initialized\n";
        return -1;
    }

    std::cout << "Opening windows window\n";

    m_hwindow = CreateWindowEx(
        0,
        L"oxygenWindowClass",
        get_wstring_name().c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, m_hinstance, nullptr
    );

    if (!m_hwindow) {
        std::cout << "Failed to create window\n";
        return -1;
    }

    ShowWindow(m_hwindow, SW_SHOW);

    MSG msg = {};
    m_is_running = true;

    while (m_is_running) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                m_is_running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // update here
    
    }
    

    return 0;
}

std::wstring neon::WindowsWindow::get_wstring_name()
{
    if (m_name.empty()) return std::wstring();

    int wideCharLength = MultiByteToWideChar(CP_UTF8, 0, m_name.c_str(), -1, nullptr, 0);
    if (wideCharLength == 0) {
        // Handle error
        throw std::runtime_error("MultiByteToWideChar failed");
    }

    std::wstring output(wideCharLength, 0);
    int result = MultiByteToWideChar(CP_UTF8, 0, m_name.c_str(), -1, &output[0], wideCharLength);
    if (result == 0) {
        // Handle error
        throw std::runtime_error("MultiByteToWideChar failed");
    }

    // Remove null terminator included by Windows API
    output.resize(wideCharLength - 1);
    return output;
}

#endif
