#pragma once

#include <string>
#include <memory>

#include "oxygen/outcome.hpp"

namespace neon
{

class Window;

xgn::OutcomeOr<std::unique_ptr<Window>> create_window(const std::string &name);

class Window
{
public:
    Window(const std::string &name);

    virtual ~Window() = default;

    virtual xgn::Outcome init() = 0;
    
    virtual xgn::Outcome swap_buffers() {return xgn::outcome_ok(); };

    virtual xgn::Outcome poll_events() {return xgn::outcome_ok(); };

    virtual bool should_close() = 0;

protected:
    std::string m_name;

    bool m_is_initialized;

    bool m_is_running;
private:    


};


}