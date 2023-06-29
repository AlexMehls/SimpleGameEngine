# SimpleGameEngine
A simple game engine based on OpenGL

This repository contains a demo project with some example test levels. All project specific files are contained in the "Project" folder (aside from "main.cpp").

## Used Libraries
- Glad
- GLFW
- GLM
- Assimp
- stb_image
- nlohmann/json
- (imgui) (editor not implemented)

## Setup
All necessary libraries are included in the repository. While most libraries are included as source-code, glfw3 is a precompiled binary that requires the Visual Studio 2022 compiler. To install this compiler, download Visual Studio Comunity 2022 and install the MSVC 2022 C++ build tools.
CMake is required for the build system. After installing CMake, run CMake using the top level CMakeLists.txt. Compiling the libraries will take a while when comiling for the first time.

## Supported (and tested) asset file formats
### Meshes
- OBJ
### Textures
- PNG

## Scripting
New behavior components should inherit from the "Behavior" class. For examples how to implement a new custom behavior, take a look at the example project scripts. Provided that the script files are in the correct folders, they will be found and compiled automatically when running the build system.

There are 3 main methods that need to be implemented:
- loadDefaultValues(): Initializes membervariables (with default values that can be specified in the level file).
- update(double deltaTime): This method is executed once per frame.
- fixedUpdate(double deltaTime): This method is executed in small fixed time steps (usually multiple times per frame).

## Levels
Levels are stored as JSON files. They can be created manually or programmatically. For examples take a look at the level files of the example project or the level creation functions in "main.cpp".

## Button Mapping
Button mappings are defined by config files stored in the JSON format. They can be created manually or programmatically. For examples take a look at the config file of the example project or the config creation function in "main.cpp".