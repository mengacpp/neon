#ifdef _WIN32

#include "neon/windows-window.hpp"

#include <string>
#include <locale>
#include <codecvt>

std::wstring string_to_wstring(const std::string &str);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

neon::WindowsWindow::WindowsWindow(const std::string &name)
: Window(name)
{
}

void neon::WindowsWindow::init()
{
    m_hinstance = GetModuleHandle(nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = m_hinstance;
    wc.lpszClassName = L"oxygenWindowClass";

    if (!RegisterClass(&wc)) {
        throw std::runtime_error("registration of window class 'oxygenWindowClass' failed.");
    }

    std::cout << "window initialized\n";
    m_is_initialized = true;
}

void neon::WindowsWindow::open()
{
    if(!m_is_initialized)
    {
        throw std::runtime_error("opening failed on '" + m_name + "': not initialized. call window::init() if you haven't to fix, or handle initialization errors first.");
    }

    std::cout << "Opening windows window\n";

    m_hwindow = CreateWindowEx(
        0,
        L"oxygenWindowClass",
        string_to_wstring(m_name).c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, m_hinstance, nullptr
    );

    if (!m_hwindow) {
        throw std::runtime_error("opening failed on'" + m_name + "': creation failed.");
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
    

}

std::wstring string_to_wstring(const std::string &str)
{
    if (str.empty()) return std::wstring();

    int wideCharLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (wideCharLength == 0) {
        throw std::runtime_error("MultiByteToWideChar failed");
    }

    std::wstring output(wideCharLength, 0);
    int result = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &output[0], wideCharLength);
    if (result == 0) {
        throw std::runtime_error("MultiByteToWideChar failed");
    }

    // Remove null terminator included by Windows API
    output.resize(wideCharLength - 1);
    return output;
}

#endif
