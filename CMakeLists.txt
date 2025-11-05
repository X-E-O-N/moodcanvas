cmake_minimum_required(VERSION 3.5)
project(MoodCanvas C)

set(CMAKE_C_STANDARD 99)

# Set output executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add source files
file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Find raylib package
find_package(raylib QUIET)

# If raylib is not installed as a system package, fetch & build it locally
if (NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/heads/master.zip
    )

    FetchContent_MakeAvailable(raylib)
endif()

add_executable(MoodCanvas ${SRC_FILES})

# Link raylib and system dependencies
target_link_libraries(MoodCanvas raylib m pthread dl rt)

# Linux / macOS / Windows specifics
if (APPLE)
    target_link_libraries(MoodCanvas "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(MoodCanvas GL X11)
elseif(WIN32)
    target_link_libraries(MoodCanvas opengl32 gdi32 winmm)
endif()
