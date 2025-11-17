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

```bash
cmake .
cmake --build .
./build/MoodCanvas
