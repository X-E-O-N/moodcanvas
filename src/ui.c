#include <raylib.h>
#include "ui.h"

void DrawMoodButtons(Mood currentMood, Mood *clickedMood) {

    Rectangle btns[MOOD_COUNT] = {
        {10, 10, 100, 30},
        {120, 10, 100, 30},
        {230, 10, 100, 30},
        {340, 10, 100, 30}
    };

    const char *labels[MOOD_COUNT] = {"Calm", "Happy", "Angry", "Sad"};

    DrawRectangle(0, 0, GetScreenWidth(), 50, (Color){230, 230, 230, 255});

    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < MOOD_COUNT; i++) {
        Color btnColor = LIGHTGRAY;

        if (CheckCollisionPointRec(mouse, btns[i])) {
            btnColor = GRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) *clickedMood = i;
        }

        if(currentMood == i) btnColor = DARKGRAY;

        DrawRectangleRec(btns[i], btnColor);
        DrawText(labels[i], btns[i].x + 25, btns[i].y + 10, 12, BLACK);
    }  

}
