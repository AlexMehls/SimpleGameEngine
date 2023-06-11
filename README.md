# SimpleGameEngine
A simple game engine based on OpenGL

## Used Libraries:
- Glad
- GLFW
- GLM
- Assimp
- stb_image
- imgui
- nlohmann/json

## Setup:
All necessary libraries are included in the repository. While most libraries are included as source-code, glfw3 is a precompiled binary that requires the Visual Studio 2022 compiler.
To install this compiler, download Visual Studio Comunity 2022 and install the MSVC 2022 C++ build tools.
CMake is required for the build system. After installing CMake, run CMake using the top level CMakeLists.txt. Compiling the libraries will take a while when comiling for the first time.

## Supported (and tested) asset file formats:
### Meshes:
- OBJ
### Textures:
- PNG
