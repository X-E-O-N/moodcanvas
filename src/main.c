#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "canvas.h"
#include "mood.h"
#include "ui.h"

#define UI_HEIGHT 90

// initialize/declare global variables

char statusText[64];
int statusTimer = 0;
Canvas canvas;
Color selectedColor;
int brushSize;
float brushOpacity;
bool eraserMode = false;
Vector2 lp = {0, 0};
UIState uiState;

// save image function

void SaveCanvas(const char *filename) {
    char full[64];
    snprintf(full, 64, "exports/%s.png", filename);

    Image img = LoadImageFromTexture(canvas.texture.texture);
    ImageFlipVertical(&img);
    ExportImage(img, full);
    UnloadImage(img);

    strcpy(statusText, "Saved!");
    statusTimer = 120;
}

// load image function

void LoadCanvas(const char *filename) {
    char full[64];
    if (strstr(filename, ".png") != NULL) {
        snprintf(full, sizeof(full), "exports/%s", filename);
    } else {
        snprintf(full, sizeof(full), "exports/%s.png", filename);
    }

    Image img = LoadImage(full);
    if (!img.data) {
        strcpy(statusText, "Load failed.");
        statusTimer = 120;
        return;
    }

    ImageFlipVertical(&img);
    if (img.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
        ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    }
    UpdateTexture(canvas.texture.texture, img.data);

    UnloadImage(img);

    strcpy(statusText, "Loaded!");
    statusTimer = 120;
}

int main(void){

    // initialize window and canvas

    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "raylib test");
    SetTargetFPS(60);

    canvas = CreateCanvas(screenWidth, screenHeight);

    // set brush and canvas properties from default mood, sync to ui

    Mood currentMood = MOOD_CALM;
    Mood clickedMood = currentMood;
    MoodProfile moodProfile = GetMoodProfile(currentMood);

    selectedColor = moodProfile.brushColor;
    uiState.brushSize = moodProfile.brushSize;
    uiState.brushOpacity = moodProfile.brushOpacity;
    uiState.eraser = false;
    uiState.sizeLevel = 1;
    uiState.opacityLevel = 1;
    brushSize = uiState.brushSize;
    brushOpacity = uiState.brushOpacity;
    eraserMode = uiState.eraser;

    mkdir("exports", 0777);

    // runtime

    while (!WindowShouldClose()){

        // click a mood button to change to the corresponding mood

        if (clickedMood != currentMood) {
            currentMood = clickedMood;
            MoodProfile newProfile = GetMoodProfile(currentMood);


            // change brush properties according to selected mood

            selectedColor = newProfile.brushColor;
            uiState.brushSize = newProfile.brushSize;
            uiState.brushOpacity = newProfile.brushOpacity;
            uiState.eraser = false;
            uiState.requestClear = false;

            // quantize brush properties to levels dictated by the ui

            if (uiState.brushSize <= 5) uiState.sizeLevel = 0;
            else if (uiState.brushSize <= 12) uiState.sizeLevel = 1;
            else uiState.sizeLevel = 2;

            if (uiState.brushOpacity <= 0.3f) uiState.opacityLevel = 0;
            else if (uiState.brushOpacity <= 0.8f) uiState.opacityLevel = 1;
            else uiState.opacityLevel = 2;


            moodProfile = newProfile;

            // draw canvas bg

            BeginCanvasDraw(&canvas);
            ClearBackground(moodProfile.backgroundColor);
            EndCanvasDraw();
        }

        // clear canvas

        if (uiState.requestClear) {
            BeginCanvasDraw(&canvas);
            ClearBackground(moodProfile.backgroundColor);
            EndCanvasDraw();

            uiState.requestClear = false;
        }

        // drawing logic
        
        Vector2 mp = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mp.y > UI_HEIGHT) {
            lp = mp;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mp.y > UI_HEIGHT) { 
            BeginCanvasDraw(&canvas);
            Color drawCol = eraserMode ? moodProfile.backgroundColor : Fade(selectedColor, brushOpacity);
            DrawLineEx(lp, mp, brushSize * 2.2f, drawCol);
            DrawCircleV(mp, brushSize, drawCol);

            EndCanvasDraw();
            lp = mp;
        } 

        // draw canvas and ui elements

        BeginDrawing();
        ClearBackground(moodProfile.backgroundColor);

        DrawCanvas(&canvas);
        DrawMoodButtons(currentMood, &clickedMood, &selectedColor, &uiState);

        // set brush properties according to selected settings

        brushSize = uiState.brushSize;
        brushOpacity = uiState.brushOpacity;
        eraserMode = uiState.eraser;

        // draw circle on cursor/current stroke area

        if (mp.y > 80) {
            if (!eraserMode) {
                DrawCircleLines(mp.x, mp.y, brushSize, selectedColor);
            } else {
                DrawCircleLines(mp.x, mp.y, brushSize, RED);
            }
        }

        // display status timer

        if (statusTimer > 0) {
            DrawText(statusText, 20, screenHeight - 40, 20, BLACK);
            statusTimer--;
        }

                // save dialog logic

        if (uiState.dialog == UI_SAVE_DIALOG) {
            DrawRectangle(200, 200, 400, 200, (Color){200,200,200,240});
            DrawText("Enter name:", 230, 220, 20, BLACK);

            DrawRectangle(230, 250, 350, 30, WHITE);
            DrawText(uiState.fileNameInput, 235, 255, 20, BLACK);

            Rectangle saveBtn = {280, 300, 100, 30};
            DrawRectangleRec(saveBtn, LIGHTGRAY);
            DrawText("Save", saveBtn.x + 32, saveBtn.y + 8, 12, BLACK);

            Rectangle cancelBtn = {420, 300, 100, 30};
            DrawRectangleRec(cancelBtn, LIGHTGRAY);
            DrawText("Cancel", cancelBtn.x + 25, cancelBtn.y + 8, 12, BLACK);

            int key = GetCharPressed();
            if (key >= 32 && key < 125 && uiState.typingPosition < 31) {
                uiState.fileNameInput[uiState.typingPosition++] = (char) key;
                uiState.fileNameInput[uiState.typingPosition] = '\0';
            }
            if (IsKeyPressed(KEY_BACKSPACE) && uiState.typingPosition > 0) {
                uiState.fileNameInput[--uiState.typingPosition] = '\0';
            }
            if (CheckCollisionPointRec(mp, saveBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (strlen(uiState.fileNameInput) > 0) {
                    SaveCanvas(uiState.fileNameInput);
                }
                uiState.dialog = UI_NONE;
            }
            if (CheckCollisionPointRec(mp, cancelBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                uiState.dialog = UI_NONE;
            }
        }

        // load dialog logic

        if (uiState.dialog == UI_LOAD_DIALOG) {
            DrawRectangle(150, 150, 500, 350, (Color){200,200,200,240});
            DrawText("Choose Image:", 180, 160, 20, BLACK);

            DIR *d = opendir("exports");
            struct dirent *dir;
            int yOffset = 200;

            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if (strstr(dir->d_name, ".png")) {
                        Rectangle fileBtn = {180, yOffset - 2, 300, 22};
                        DrawRectangleRec(fileBtn, LIGHTGRAY);
                        DrawText(dir->d_name, 180, yOffset, 18, BLACK);

                        if (CheckCollisionPointRec(mp, fileBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            LoadCanvas(dir->d_name);
                            uiState.dialog = UI_NONE;
                        }
                        yOffset += 30;
                    }
                }
                closedir(d);
            }
            Rectangle cancelBtn = {420, 300, 100, 30};
            DrawRectangleRec(cancelBtn, LIGHTGRAY);
            DrawText("Cancel", cancelBtn.x + 25, cancelBtn.y + 8, 12, BLACK);

            if (CheckCollisionPointRec(mp, cancelBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                uiState.dialog = UI_NONE;
            }
        }

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
