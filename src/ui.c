#include <raylib.h>
#include "ui.h"

void DrawMoodButtons(void) {
    DrawRectangle(0, 0, GetScreenWidth(), 50, (Color){230, 230, 230, 255});

    DrawRectangle(10, 10, 100, 30, LIGHTGRAY);
    DrawText("Calm", 35, 17, 12, BLACK);

    DrawRectangle(120, 10, 100, 30, LIGHTGRAY);
    DrawText("Happy", 140, 17, 12, BLACK);

    DrawRectangle(230, 10, 100, 30, LIGHTGRAY);
    DrawText("Angry", 255, 17, 12, BLACK);

    DrawRectangle(340, 10, 100, 30, LIGHTGRAY);
    DrawText("Sad", 370, 17, 12, BLACK);
}
