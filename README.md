# MoodCanvas

MoodCanvas is a drawing application built with raylib that adapts its interface and drawing tools based on the user's selected mood (Calm, Happy, Angry, or Sad). The application will change color scheme, brush characteristics, and UI behavior depending on the chosen mood to influence the user's drawing experience.

## Vision & Core Concept

MoodCanvas aims to explore how digital tools can influence creativity and emotional expression. By linking visual elements (colors, brush styles, UI feedback) to emotional themes, the program promotes a mood-driven drawing experience. Future versions will include mood-based brushes, mood transitions, layering, saving/loading, and exporting artworks.

## Build & Run Instructions (CMake)

### Requirements
- C compiler (GCC/Clang)
- CMake 3.5+
- raylib installed on system

### Build Steps

#### Prerequisites for Windows:
- MinGW-w64 (https://www.mingw-w64.org/)
- CMake (https://cmake.org/download/)
- raylib (https://github.com/raysan5/raylib/releases)

#### CMakeLists.txt Content:
cmake_minimum_required(VERSION 3.10)
project(MoodCanvas C)

set(CMAKE_C_STANDARD 99)

set(RAYLIB_DIR "C:/libs/raylib")  # Change this to raylib directory

include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

file(GLOB SRC_FILES "src/*.c")

add_executable(MoodCanvas ${SRC_FILES})

target_link_libraries(MoodCanvas raylib opengl32 gdi32 winmm)

#### Build Commands
mkdir build
cd build
cmake ..
cmake --build . --config Release

./Release/MoodCanvas.exe # Run

```bash
cmake .
cmake --build .
./build/MoodCanvas
