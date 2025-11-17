#include <raylib.h>
#include "canvas.h"
#include "mood.h"
#include "ui.h"

int main(void){
    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "raylib test");
    SetTargetFPS(60);
    Canvas canvas = CreateCanvas(screenWidth, screenHeight);

    Mood currentMood = MOOD_CALM;
    Mood clickedMood = currentMood;
    MoodProfile moodProfile = GetMoodProfile(MOOD_CALM);

    while (!WindowShouldClose()){
        if (clickedMood != currentMood) {
            currentMood = clickedMood;
            moodProfile = GetMoodProfile(currentMood);

            BeginCanvasDraw(&canvas);
            ClearBackground(moodProfile.backgroundColor);
            EndCanvasDraw();
        }
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mp = GetMousePosition();

            BeginCanvasDraw(&canvas);
            Color brushColor = Fade(moodProfile.brushColor, moodProfile.brushOpacity);
            DrawCircleV(mp, moodProfile.brushSize, brushColor);
            EndCanvasDraw();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCanvas(&canvas);
        DrawMoodButtons(currentMood, &clickedMood);

        EndDrawing();
    }

    UnloadRenderTexture(canvas.texture);
    CloseWindow();
    return 0;
}
