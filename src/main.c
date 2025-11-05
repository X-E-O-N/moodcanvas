/* test_window.c */
#include <raylib.h>
#include "canvas.h"
#include "ui.h"

int main(void){
    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "raylib test");
    SetTargetFPS(60);
    Canvas canvas = CreateCanvas(screenWidth, screenHeight);

    while (!WindowShouldClose()){
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mp = GetMousePosition();
            BeginCanvasDraw(&canvas);
            DrawCircleV(mp, 5, BLACK);
            EndCanvasDraw();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCanvas(&canvas);
        DrawMoodButtons();

        EndDrawing();
    }

    UnloadRenderTexture(canvas.texture);
    CloseWindow();
    return 0;
}
