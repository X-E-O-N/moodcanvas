#include <raylib.h>
#include <string.h>
#include "ui.h"
#include "mood.h"

void DrawMoodButtons(Mood currentMood, Mood *clickedMood, Color *selectedColor, UIState *uiState) {


    // ui ribbon

    DrawRectangle(0, 0, GetScreenWidth(), 90, WHITE);

    // mood buttons

    Rectangle btns[MOOD_COUNT] = {
        {10, 10, 100, 30},
        {120, 10, 100, 30},
        {230, 10, 100, 30},
        {340, 10, 100, 30}
    };

    const char *labels[MOOD_COUNT] = {"Calm", "Happy", "Angry", "Sad"};

    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < MOOD_COUNT; i++) {
        Color btnColor = LIGHTGRAY;

        if (CheckCollisionPointRec(mouse, btns[i])) {
            btnColor = GRAY;
            DrawRectangleLinesEx(btns[i], 2, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) *clickedMood = i;
        }

        if(currentMood == i) btnColor = DARKGRAY;

        DrawRectangleRec(btns[i], btnColor);
        DrawText(labels[i], btns[i].x + 25, btns[i].y + 10, 12, BLACK);
    }  

    // color swatches

    Rectangle swatches[9];
    Color palette[9] = {WHITE, LIGHTGRAY, GRAY, DARKGRAY, BLACK, RED, BLUE, YELLOW};

    for (int i = 0; i < 9; i++) {
        swatches[i] = (Rectangle){10 + i*40, 50, 30, 30};
        DrawRectangleRec(swatches[i], palette[i]);
        if(CheckCollisionPointRec(mouse, swatches[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            DrawRectangleLinesEx(swatches[i], 2, BLACK);
            *selectedColor = palette[i];
        } 
    }

    // size buttons

    DrawText("Size", 520, 20, 12, BLACK);
    Rectangle sizeBtns[3] = {
        {560, 15, 40, 20},
        {605, 15, 40, 20},
        {650, 15, 40, 20},
    };
    const char *sizeLabels[3] = {"S", "M", "L"};

    for (int i = 0; i < 3; i++) {
        Color c = (uiState->sizeLevel == i) ? DARKGRAY : LIGHTGRAY;
        DrawRectangleRec(sizeBtns[i], c);
        DrawText(sizeLabels[i], sizeBtns[i].x + 12, sizeBtns[i].y + 4, 12, BLACK);

        if (CheckCollisionPointRec(mouse, sizeBtns[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            uiState->sizeLevel = i;
            if (i == 0) uiState->brushSize = 4;
            else if (i == 1) uiState->brushSize = 10;
            else if (i == 2) uiState->brushSize = 18;
        }
    }

    // opacity buttons

    DrawText("Opacity:", 500, 55, 12, BLACK);
    Rectangle opBtns[3] = {
        {560, 50, 40, 20},
        {605, 50, 40, 20},
        {650, 50, 40, 20}
    };
    const char *opLabels[3] = {"20%", "60%", "100%"};

    for (int i = 0; i < 3; i++) {
        Color c = (uiState->opacityLevel == i) ? DARKGRAY : LIGHTGRAY;
        DrawRectangleRec(opBtns[i], c);
        DrawText(opLabels[i], opBtns[i].x + 8, opBtns[i].y + 4, 10, BLACK);

        if (CheckCollisionPointRec(mouse, opBtns[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            uiState->opacityLevel = i;
            if (i == 0) uiState->brushOpacity = 0.20f;
            else if (i == 1) uiState->brushOpacity = 0.60f;
            else if (i == 2) uiState->brushOpacity = 1.0f;
        }
    }

    // eraser button

    Rectangle eraserBtn = {710, 10, 80, 30};
    DrawRectangleRec(eraserBtn, uiState->eraser? DARKGRAY : LIGHTGRAY);
    DrawText("Eraser", eraserBtn.x + 20, eraserBtn.y + 8, 12, BLACK);

    if (CheckCollisionPointRec(mouse, eraserBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        uiState->eraser = !uiState->eraser;
    }

    // clear button

    Rectangle clearBtn = {710, 45, 80, 30};
    DrawRectangleRec(clearBtn, LIGHTGRAY);
    DrawText("Clear", clearBtn.x + 20, clearBtn.y + 8, 12, BLACK);

    if (CheckCollisionPointRec(mouse, clearBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        uiState->requestClear = true;
    }

    // save button

    Rectangle saveBtn = {930, 10, 80, 30};
    DrawRectangleRec(saveBtn, LIGHTGRAY);
    DrawText("Save", saveBtn.x + 20, saveBtn.y + 8, 12, BLACK);
    if (CheckCollisionPointRec(mouse, saveBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        uiState->dialog = UI_SAVE_DIALOG;
        strcpy(uiState->fileNameInput, "");
        uiState->typingPosition = 0;
    }

    Rectangle loadBtn = {930, 45, 80, 30};
    DrawRectangleRec(loadBtn, LIGHTGRAY);
    DrawText("Load", loadBtn.x + 20, loadBtn.y + 8, 12, BLACK);
    if (CheckCollisionPointRec(mouse, loadBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        uiState->dialog = UI_LOAD_DIALOG;
    }


}
