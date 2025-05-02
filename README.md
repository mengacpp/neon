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