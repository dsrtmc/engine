# Engine

"Engine" is a very aptly named project that's eventually to resemble a basic game engine. As of right now, it's in a state that just facilitates playing around with OpenGL, although still enabling one to treat it as a game engine with a few tweaks to personal liking.
*Highly inspired by [Hazel](https://github.com/TheCherno/Hazel)*

## Getting Started

__<ins>1. Clone the repository and its submodules:</ins>__

   `git clone --recurse-submodules https://github.com/dsrtmc/engine.git`
  
   If the repository was cloned non-recursively first, use: `git submodule update --init` instead.

__<ins>2. Configuring the dependencies:</ins>__
   
   1. Build [spdlog](https://github.com/gabime/spdlog):
      
      ```bash
      cd Engine/vendor/spdlog
      mkdir build
      cd build
      cmake ..
      make
      ```
   3. Fix [imgui](https://github.com/ocornut/imgui)'s GLFW imports:
      
      Go to `Engine/vendor/imgui/backends/` and edit the file `imgui_impl_glfw.cpp`:
      ```cpp
      // #include <GLFW/glfw3.h>              // Comment this include out
      #include "../glfw/include/GLFW/glfw3.h" // and add this line instead
      ```
      The reason for that is I've spent way too long trying to link imgui into the project without relying on relative paths, therefore I temporarily left it like that.
      
__<ins>3. Build the project:</ins>__

   ```bash
   # current directory: engine/
   mkdir build
   cd build
   cmake ..
   make
   ```

__<ins>4. Run the desired sub-project:</ins>__

   ```bash
   # current directory: engine/cmake-build-(debug/release)/Sandbox/
   ./sandbox

   # current directory: engine/cmake-build-(debug/release)/Game/
   ./game
   ```
   **NOTE: You must be inside the `engine/build/<project name>/` folder before running the executable, because as of right now all filepaths are relative.**
