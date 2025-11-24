#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "mood.h"

typedef enum {
    UI_NONE = 0,
    UI_SAVE_DIALOG,
    UI_LOAD_DIALOG
} DialogState;

typedef struct {
    int brushSize;
    float brushOpacity;
    bool eraser;
    bool requestClear;

    int sizeLevel;
    int opacityLevel;

    DialogState dialog;
    char fileNameInput[32];
    int typingPosition;
} UIState;

void DrawMoodButtons(Mood currentMood, Mood *clickedMood, Color *selectedColor, UIState *uiState);

#endif
