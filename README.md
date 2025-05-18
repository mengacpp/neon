# Neon

Neon is a cross-platform abstraction library that simplifies window creation and input handling.

## Building

Before building Neon, make sure you installed [oxygen](https://github.com/mengacpp/oxygen) on your device, and then follow these steps:

1. **Clone the repostory on your device**

    ```bat
    git clone https://github.com/mengacpp/neon.git 
    ```

2. **navigate in the directory where you cloned the repostory and run CMake**

    ```bat
    cmake -B build
    cmake --build build
    ```

3. **You'll find the `.a` static library file in `build/`**

## Example

Here is how you would create a window using Neon. [xgn::Outcome](https://github.com/mengacpp/oxygen) module is used for error handling.

```c++
#include "neon/window.hpp"

int main()
{
  std::unique_ptr<neon::Window> window;

  {
    xgn::OutcomeOr<std::unique_ptr<neon::Window>> out 
      = neon::create_window("Neondow");

    if(!out.is_ok()) {
      std::cout << out.outcome().fatal_message();
      return -1;
    }

    window = *(std::move(out));
  }

  {
    xgn::Outcome out = window->init();
    if(!out.is_ok())
    {
      std::cout << out.fatal_message();
      return -1;
    }
  }

  while (!window->should_close()) {
      window->swap_buffers();

      // render here [not yet :)]
      
      window->poll_events();
  }
}
```
